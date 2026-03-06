`include "single_node_fsm.sv"
`define DATA_WIDTH 18
`define COLUMN_DEPTH 29
`define CENTER_NODE 15 // 1/2 of COLUMN_DEPTH
`define MAX_HEIGHT 3 // 1/8 to avoid overflow (1 << 3)
`define STEP_INCREMENT ((18'sd1 <<< 17) / ((1 <<< `MAX_HEIGHT) * `CENTER_NODE))  //(MAX_HEIGHT) / CENTER_NODE



module single_column_wave_equation #(
    parameter integer ETA_SHIFT = 10
)
(
    input logic clk,
    input logic rst,
    input logic signed [17:0] rho_eff, 
    input logic signed [17:0] G_tension,
    input logic signed [17:0] initial_value,
    input logic next_sample,
    output logic signed [17:0] wave_value,
    output logic done
);

    // compute I/O
    logic signed [17:0] u_up, u_down, compute_out;

    // pipeline registers for center node values (fed from M10K memories)
    logic signed [17:0] u_center;     // u_curr from mem_N
    logic signed [17:0] u_center_prev; // u_prev from mem_Nm1

    // memory N (current timestep) signals
    logic signed [17:0] mem_N_rdata, mem_N_wdata;
    logic [$clog2(`COLUMN_DEPTH)-1:0] mem_N_waddr, mem_N_raddr;
    logic mem_N_we;

    // memory Nm1 (previous timestep) signals
    logic signed [17:0] mem_Nm1_rdata, mem_Nm1_wdata;
    logic [$clog2(`COLUMN_DEPTH)-1:0] mem_Nm1_waddr, mem_Nm1_raddr;
    logic mem_Nm1_we;

    // init write counter
    logic [$clog2(`COLUMN_DEPTH)-1:0] init_addr;

    // node processing counter
    logic [$clog2(`COLUMN_DEPTH)-1:0] node_count;

    // combinational triangle-wave value for initialization
    wire signed [17:0] triangle_value = (init_addr <= `CENTER_NODE) ?
        init_addr * `STEP_INCREMENT :
        (`COLUMN_DEPTH - 1 - init_addr) * `STEP_INCREMENT;

    // address increment helpers (continuous assignments)
    wire [$clog2(`COLUMN_DEPTH)-1:0] next_N_raddr   = (mem_N_raddr   == `COLUMN_DEPTH-1) ? '0 : mem_N_raddr   + 1;
    wire [$clog2(`COLUMN_DEPTH)-1:0] next_Nm1_raddr = (mem_Nm1_raddr == `COLUMN_DEPTH-1) ? '0 : mem_Nm1_raddr + 1;
    wire [$clog2(`COLUMN_DEPTH)-1:0] next_N_waddr   = (mem_N_waddr   == `COLUMN_DEPTH-1) ? '0 : mem_N_waddr   + 1;
    wire [$clog2(`COLUMN_DEPTH)-1:0] next_Nm1_waddr = (mem_Nm1_waddr == `COLUMN_DEPTH-1) ? '0 : mem_Nm1_waddr + 1;

    // ---- Memory Instances ----
    M10K_COLUMN #(
        .DATA_WIDTH(`DATA_WIDTH),
        .COLUMN_DEPTH(`COLUMN_DEPTH)
    )
    mem_N (
        .q(mem_N_rdata),
        .d(mem_N_wdata),
        .write_address(mem_N_waddr),
        .read_address(mem_N_raddr),
        .we(mem_N_we),
        .clk(clk)
    );
    
    M10K_COLUMN #(
        .DATA_WIDTH(`DATA_WIDTH),
        .COLUMN_DEPTH(`COLUMN_DEPTH)
    )
    mem_Nm1 (
        .q(mem_Nm1_rdata),
        .d(mem_Nm1_wdata),
        .write_address(mem_Nm1_waddr),
        .read_address(mem_Nm1_raddr),
        .we(mem_Nm1_we),
        .clk(clk)
    );

    // combinational node compute   
    single_node_wave_equation #(
        .ETA_SHIFT(ETA_SHIFT)
    )
    compute (
        .rho_eff(rho_eff),
        .u_curr(u_center),       // from mem_N
        .u_prev(u_center_prev),  // from mem_Nm1
        .u_up(u_up),
        .u_down(u_down),
        .u_next(compute_out)
    );

    // FSM states 
    typedef enum logic [2:0] {
        INIT,
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6
    } state_t;
 
    state_t state, next_state;
    
    assign wave_value = u_center;


    always_ff @(posedge clk) begin
        if (rst) begin
            state <= INIT;
        end else begin
            state <= next_state;
        end
    end

    // combinational next state logic 
    always_comb begin
        next_state = state; // default: hold current state
        case (state)
            INIT:    next_state = (init_addr == `COLUMN_DEPTH-1) ? STATE_0 : INIT;
            STATE_0: next_state = STATE_1;
            STATE_1: next_state = STATE_2;
            STATE_2: next_state = STATE_3;
            STATE_3: next_state = STATE_4;
            STATE_4: next_state = (node_count == `COLUMN_DEPTH-1) ? STATE_5 : STATE_4;
            STATE_5: next_state = STATE_6;
            STATE_6: next_state = (next_sample) ? STATE_0 : STATE_6; // hold in done state
            default: next_state = INIT;
        endcase
    end

    // ---- Datapath ----
    always_ff @(posedge clk) begin
        if (rst) begin
            mem_N_we      <= 1;
            mem_Nm1_we    <= 1;
            mem_N_waddr   <= 0;
            mem_Nm1_waddr <= 0;
            mem_N_raddr   <= 0;
            mem_Nm1_raddr <= 0;
            mem_N_wdata   <= 18'sd0;
            mem_Nm1_wdata <= 18'sd0;
            init_addr     <= 0;
            node_count    <= 0;
            u_up          <= 18'sd0;
            u_down        <= 18'sd0;
            u_center      <= 18'sd0;
            u_center_prev <= 18'sd0;
            done          <= 0;
        end else begin
            case(state)
                INIT: begin
                    // write initial triangle wave values to both memories
                    mem_N_waddr   <= init_addr;
                    mem_Nm1_waddr <= init_addr;
                    mem_N_wdata   <= triangle_value;
                    mem_Nm1_wdata <= triangle_value;
                    init_addr     <= init_addr + 1;
                end

                STATE_0: begin
                    // stop writes, start reading from bottom of column
                    mem_N_raddr   <= 0;
                    mem_Nm1_raddr <= 0;
                    node_count    <= 0;
                    done          <= 0;
                end

                STATE_1: begin
                    // M10K latency cycle: data for addr 0 in flight
                    mem_N_raddr   <= next_N_raddr;
                    mem_Nm1_raddr <= 0;
                end

                STATE_2: begin
                    // N[0] and Nm1[0] now available on rdata
                    mem_N_raddr   <= next_N_raddr;
                    mem_Nm1_raddr <= next_Nm1_raddr;
                    u_up <= mem_N_rdata;
                end

                STATE_3: begin
                    // N[j+1] now available — latch as u_up (boundary = 0 for top node)
                    mem_N_raddr   <= next_N_raddr;
                    mem_Nm1_raddr <= next_Nm1_raddr;
                    u_up          <= mem_N_rdata;
                    u_center_prev <= mem_Nm1_rdata;
                end

                STATE_4: begin
                    mem_N_raddr   <= next_N_raddr;
                    mem_Nm1_raddr <= next_Nm1_raddr;
                    u_up          <= (mem_N_raddr != `COLUMN_DEPTH-1) ? mem_N_rdata : 18'sd0;
                    u_center      <= u_up;
                    u_center_prev <= mem_Nm1_rdata;
                    u_down        <= u_center;
                    if (node_count != `COLUMN_DEPTH-1) begin
                        node_count <= node_count + 1;
                    end
                end

                STATE_5: begin
                    // write compute result to mem_N, old u_center to mem_Nm1
                    mem_N_waddr   <= node_count;
                    mem_Nm1_waddr <= node_count;
                    mem_N_wdata   <= compute_out;        // u_next  -> new N[j]
                    mem_Nm1_wdata <= u_center;            // u_curr  -> new Nm1[j]
                end

                STATE_6: begin
                    done      <= 1;
                end

                default: begin
                end
            endcase
        end
    end

endmodule


// ---- M10K Memory Column ----
module M10K_COLUMN #(
    parameter integer DATA_WIDTH = 18,
    parameter integer COLUMN_DEPTH = 29
)
( 
    output reg [DATA_WIDTH-1:0] q,
    input [DATA_WIDTH-1:0] d,
    input [$clog2(COLUMN_DEPTH)-1:0] write_address, read_address,
    input we, clk
);
    // force M10K ram style
    reg [DATA_WIDTH-1:0] mem [COLUMN_DEPTH-1:0]  /* synthesis ramstyle = "no_rw_check, M10K" */;
        
    always @ (posedge clk) begin
        if (we) begin
            mem[write_address] <= d;
        end
        q <= mem[read_address]; // q doesn't get d in this clock cycle
    end

endmodule
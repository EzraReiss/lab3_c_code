`define DATA_WIDTH 18
`define COLUMN_DEPTH 29

module single_column_wave_equation #(
    parameter integer ETA_SHIFT = 10,
    parameter COLUMN_DEPTH = `COLUMN_DEPTH
)
(
    input logic clk,
    input logic rst,
    input logic signed [17:0] rho_eff, 
    input logic signed [17:0] G_tension,

    // Initialization interface — top module drives these
    input logic signed [17:0] init_data,
    input logic [$clog2(COLUMN_DEPTH)-1:0] init_addr,
    input logic init_we,

    // Scan interface — read any node from mem_N while IDLE
    input logic [$clog2(COLUMN_DEPTH)-1:0] scan_addr,
    output logic signed [17:0] scan_data,

    input logic signed [17:0] u_right,
    input logic signed [17:0] u_left,
    input logic next_sample,
    output logic signed [17:0] wave_value,
    output logic signed [17:0] u_middle_node,
    output logic signed [17:0] center_node_14,
    output logic done
);

    // compute I/O
    logic signed [17:0] u_up, u_down, compute_out;

    // pipeline registers for center node values (fed from M10K memories)
    logic signed [17:0] u_center;     // u_curr from mem_N
    logic signed [17:0] u_center_prev; // u_prev from mem_Nm1

    // memory N (current timestep) signals
    logic signed [17:0] mem_N_rdata, mem_N_wdata;
    logic [$clog2(COLUMN_DEPTH)-1:0] mem_N_waddr, mem_N_raddr;
    logic mem_N_we;

    // memory Nm1 (previous timestep) signals
    logic signed [17:0] mem_Nm1_rdata, mem_Nm1_wdata;
    logic [$clog2(COLUMN_DEPTH)-1:0] mem_Nm1_waddr, mem_Nm1_raddr;
    logic mem_Nm1_we;

    // node processing counter
    logic [$clog2(COLUMN_DEPTH)-1:0] node_count;
    localparam int ADDR_W = $clog2(COLUMN_DEPTH);
    localparam int CENTER_NODE = (COLUMN_DEPTH - 1) / 2;
    localparam logic [ADDR_W-1:0] LAST_IDX = ADDR_W'(COLUMN_DEPTH - 1);
    localparam logic [ADDR_W-1:0] MAX_FOR_P1 = (COLUMN_DEPTH > 1) ? ADDR_W'(COLUMN_DEPTH - 1) : '0;
    localparam logic [ADDR_W-1:0] MAX_FOR_P2 = (COLUMN_DEPTH > 2) ? ADDR_W'(COLUMN_DEPTH - 2) : '0;
    localparam logic [ADDR_W-1:0] MAX_FOR_P3 = (COLUMN_DEPTH > 3) ? ADDR_W'(COLUMN_DEPTH - 3) : '0;
    localparam logic [ADDR_W-1:0] MAX_FOR_P4 = (COLUMN_DEPTH > 4) ? ADDR_W'(COLUMN_DEPTH - 4) : '0;
    localparam logic [ADDR_W-1:0] CENTER_NODE_IDX = CENTER_NODE[ADDR_W-1:0];

    // node_count-based address helpers (bounded at top boundary)
    wire [ADDR_W-1:0] node_addr     = node_count;
    wire [ADDR_W-1:0] node_addr_p1  = (node_count < MAX_FOR_P1) ? (node_count + ADDR_W'(1)) : LAST_IDX;
    wire [ADDR_W-1:0] node_addr_p2  = (node_count < MAX_FOR_P2) ? (node_count + ADDR_W'(2)) : LAST_IDX;
    wire [ADDR_W-1:0] node_addr_p3  = (node_count < MAX_FOR_P3) ? (node_count + ADDR_W'(3)) : LAST_IDX;
    wire [ADDR_W-1:0] node_addr_p4  = (node_count < MAX_FOR_P4) ? (node_count + ADDR_W'(4)) : LAST_IDX;

    // ---- Memory Instances ----
    M10K_COLUMN #(
        .DATA_WIDTH(`DATA_WIDTH),
        .COLUMN_DEPTH(COLUMN_DEPTH)
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
        .COLUMN_DEPTH(COLUMN_DEPTH)
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
        .u_right(u_right),
        .u_left(u_left),
        .u_down(u_down),
        .u_next(compute_out)
    );

    // FSM states
    typedef enum logic [2:0] {
        IDLE,
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
    assign scan_data  = mem_N_rdata;

    always_ff @(posedge clk) begin
        if (rst) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // combinational next state logic 
    always_comb begin
        next_state = state;
        case (state)
            IDLE: begin
                if (next_sample) next_state = STATE_0;
                else             next_state = IDLE;
            end
            STATE_0: next_state = STATE_1;
            STATE_1: next_state = STATE_2;
            STATE_2: next_state = STATE_3;
            STATE_3: next_state = STATE_4;
            STATE_4: begin
                if (node_count == LAST_IDX) next_state = STATE_5;
                else                        next_state = STATE_4;
            end
            STATE_5: next_state = STATE_6;
            STATE_6: next_state = IDLE;
            default: next_state = IDLE;
        endcase
    end

    // ---- Datapath ----
    always_ff @(posedge clk) begin
        if (rst) begin
            mem_N_we      <= 0;
            mem_Nm1_we    <= 0;
            mem_N_waddr   <= 0;
            mem_Nm1_waddr <= 0;
            mem_N_raddr   <= 0;
            mem_Nm1_raddr <= 0;
            mem_N_wdata   <= 18'sd0;
            mem_Nm1_wdata <= 18'sd0;
            node_count    <= 0;
            u_up          <= 18'sd0;
            u_down        <= 18'sd0;
            u_center      <= 18'sd0;
            u_center_prev <= 18'sd0;
            center_node_14 <= 18'sd0;
            done          <= 0;
        end else if (init_we) begin
            // Top module is writing initial values — pass through to both memories
            mem_N_we      <= 1;
            mem_Nm1_we    <= 1;
            mem_N_waddr   <= init_addr;
            mem_Nm1_waddr <= init_addr;
            mem_N_wdata   <= init_data;
            mem_Nm1_wdata <= init_data;
            done          <= 0;
        end else begin
            case(state)
                IDLE: begin
                    mem_N_we     <= 0;
                    mem_Nm1_we   <= 0;
                    mem_N_raddr  <= scan_addr;
                    done         <= 1;
                end

                STATE_0: begin
                    mem_N_we      <= 0;
                    mem_Nm1_we    <= 0;
                    mem_N_raddr   <= 0;
                    mem_Nm1_raddr <= 0;
                    node_count    <= 0;
                    done          <= 0;
                end

                STATE_1: begin
                    mem_N_we      <= 0;
                    mem_Nm1_we    <= 0;
                    mem_N_raddr   <= node_addr_p1;
                    mem_Nm1_raddr <= node_addr;
                end

                STATE_2: begin
                    mem_N_we      <= 0;
                    mem_Nm1_we    <= 0;
                    mem_N_raddr   <= node_addr_p2;
                    mem_Nm1_raddr <= node_addr_p1;
                    u_up <= mem_N_rdata;
                end

                STATE_3: begin
                    mem_N_we      <= 0;
                    mem_Nm1_we    <= 0;
                    mem_N_raddr   <= node_addr_p3;
                    mem_Nm1_raddr <= node_addr_p2;
                    u_up          <= mem_N_rdata;
                    u_center      <= u_up;
                    u_down        <= 18'sd0;
                    u_center_prev <= mem_Nm1_rdata;
                    mem_N_waddr   <= LAST_IDX;
                    mem_Nm1_waddr <= LAST_IDX;
                end

                STATE_4: begin
                    mem_N_we      <= 1;
                    mem_Nm1_we    <= 1;
                    mem_N_raddr   <= node_addr_p4;
                    mem_Nm1_raddr <= node_addr_p3;
                    mem_N_waddr   <= node_addr;
                    mem_Nm1_waddr <= node_addr;
                    mem_N_wdata   <= (node_count == 0) ? 18'sd0 : compute_out;
                    mem_Nm1_wdata <= (node_count == 0) ? 18'sd0 : u_center;
                    u_up          <= (node_count == LAST_IDX) ? 18'sd0 : mem_N_rdata;
                    u_center      <= u_up;
                    u_center_prev <= mem_Nm1_rdata;
                    u_down        <= u_center;
                    if (node_count == CENTER_NODE_IDX) begin
                        center_node_14 <= u_center;
                        u_middle_node  <= u_center;
                    end
                    if (node_count != LAST_IDX) begin
                        node_count <= node_count + 1;
                    end
                end

                STATE_5: begin
                    mem_N_we      <= 1;
                    mem_Nm1_we    <= 1;
                    mem_N_waddr   <= node_addr;
                    mem_Nm1_waddr <= node_addr;
                    mem_N_wdata   <= 18'sd0;
                    mem_Nm1_wdata <= 18'sd0;
                end

                STATE_6: begin
                    mem_N_we  <= 0;
                    mem_Nm1_we <= 0;
                    done <= 1;
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
        q <= mem[read_address];
    end

endmodule

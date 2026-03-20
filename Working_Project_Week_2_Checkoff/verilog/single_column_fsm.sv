`define DATA_WIDTH 18
`define COLUMN_DEPTH 29

module single_column_wave_equation #(
    parameter integer ETA_SHIFT = 10,
    parameter COLUMN_DEPTH = `COLUMN_DEPTH
)
(
    input logic clk,
    input logic rst,
    input logic signed [17:0]              rho_eff, 
    input logic signed [17:0]              G_tension,
    input logic [$clog2(COLUMN_DEPTH)-1:0] drum_length,

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
    localparam int ROWS_W = ADDR_W + 1;

    logic [ROWS_W-1:0] active_rows;
    logic [ADDR_W-1:0] last_idx_dyn;
    logic [ADDR_W-1:0] center_node_idx_dyn;

    always_comb begin
        if (drum_length < ADDR_W'(2)) begin
            active_rows = ROWS_W'(2);
        end else if (drum_length > ADDR_W'(COLUMN_DEPTH)) begin
            active_rows = ROWS_W'(COLUMN_DEPTH);
        end else begin
            active_rows = ROWS_W'(drum_length);
        end

        last_idx_dyn = active_rows[ADDR_W-1:0] - ADDR_W'(1);
        center_node_idx_dyn = last_idx_dyn >> 1;
    end

    // node_count-based address helpers (bounded at top boundary)
    wire [ADDR_W-1:0] node_addr     = node_count;
    wire [ADDR_W-1:0] node_addr_p1  = (node_count + ADDR_W'(1) <= last_idx_dyn) ? (node_count + ADDR_W'(1)) : last_idx_dyn;
    wire [ADDR_W-1:0] node_addr_p2  = (node_count + ADDR_W'(2) <= last_idx_dyn) ? (node_count + ADDR_W'(2)) : last_idx_dyn;
    wire [ADDR_W-1:0] node_addr_p3  = (node_count + ADDR_W'(3) <= last_idx_dyn) ? (node_count + ADDR_W'(3)) : last_idx_dyn;
    wire [ADDR_W-1:0] node_addr_p4  = (node_count + ADDR_W'(4) <= last_idx_dyn) ? (node_count + ADDR_W'(4)) : last_idx_dyn;

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
                if (node_count == last_idx_dyn) next_state = STATE_5;
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
                    mem_N_waddr   <= last_idx_dyn;
                    mem_Nm1_waddr <= last_idx_dyn;
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
                    u_up          <= (node_count == last_idx_dyn) ? 18'sd0 : mem_N_rdata;
                    u_center      <= u_up;
                    u_center_prev <= mem_Nm1_rdata;
                    u_down        <= u_center;
                    if (node_count == center_node_idx_dyn) begin
                        center_node_14 <= u_center;
                        u_middle_node  <= u_center;
                    end
                    if (node_count != last_idx_dyn) begin
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

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
    output logic signed [17:0] wave_value,
    output logic done
    
);

    logic signed [17:0] u_up, u_down, compute_out;

    logic signed [17:0] mem_N_rdata, mem_N_wdata;
    
    logic [$clog2(COLUMN_DEPTH)-1:0] mem_N_waddr, mem_N_raddr;
    logic [$clog2(COLUMN_DEPTH)-1:0] mem_Nm1_waddr, mem_Nm1_raddr;
    
    logic [$clog2(COLUMN_DEPTH)-1:0] next_N_waddr = (mem_N_waddr == COLUMN_DEPTH-1) ? 0 : mem_N_waddr + 1;
    logic [$clog2(COLUMN_DEPTH)-1:0] next_Nm1_waddr = (mem_Nm1_waddr == COLUMN_DEPTH-1) ? 0 : mem_Nm1_waddr + 1;


    //AI generated LUT initialization and use of localparams to reduce logic utilization
    typedef logic signed [17:0] init_lut_t [0:`COLUMN_DEPTH-1];

    function automatic init_lut_t build_triangle_init_lut();
        init_lut_t lut;
        int idx;
        int center_index;
        int distance_from_edge;
        begin
            center_index = `COLUMN_DEPTH / 2;
            for (idx = 0; idx < `COLUMN_DEPTH; idx++) begin
                distance_from_edge = (idx <= center_index) ? idx : (`COLUMN_DEPTH - 1 - idx);
                lut[idx] = distance_from_edge * `STEP_INCREMENT;
            end
            build_triangle_init_lut = lut;
        end
    endfunction

    localparam init_lut_t TRIANGLE_INIT_LUT = build_triangle_init_lut();

    

    
    
    
    M10K_COLUMN #(
        .DATA_WIDTH(DATA_WIDTH),
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
        .DATA_WIDTH(DATA_WIDTH),
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

    

    

    single_node_wave_equation #(
        ETA_SHIFT (ETA_SHIFT)
    )
    compute (
        .clk(clk),
        .rst(rst),
        .rho_eff(rho_eff),
        .G_tension(G_tension),
        .initial_value(initial_value),
        .u_up(u_up),
        .u_down(u_down),
        .wave_value(compute_out)
    );

    typedef enum logic [2:0] {
     INIT,
     STATE_0,
     STATE_1,
     STATE_2,
     STATE_3,
     STATE_4,
     STATE_5,
     STATE_6,
    } state_t;
 
    state_t state, next_state;
 

always_ff @(posedge clk) begin
    if (rst) begin
        mem_N_waddr <= 0;
        mem_Nm1_waddr <= 0;
        state <= INIT;
    end else begin
        state <= next_state;
        case(state)
            INIT: begin
                mem_N_we <= 1;
                mem_Nm1_we <= 1;
                mem_N_waddr <= next_N_waddr;
                mem_Nm1_waddr <= next_N_waddr; // during init, both BRAMs are written at the same node

                mem_N_wdata <= TRIANGLE_INIT_LUT[mem_N_waddr]; //initialize N from compile-time triangle LUT
                mem_Nm1_wdata <= 0; //initialize N-1 to 0 
            end
        endcase
    end
end

//combinational next state logic
always_comb begin
    case (state)
        INIT: (next_N_waddr == 0) ? next_state = STATE_0 : next_state = INIT;

    endcase
end
 
always_ff begin
    case (state)
        INIT: begin
            
        end

        STATE_0: begin
            // Start N at bottom
            mem_N_raddr <= 0;
        end

        STATE_1: begin
            // Increment N, Nm1 now at bottom
            mem_N_raddr   <= next_read_N;
            mem_Nm1_raddr <= next_read_Nm1;
        end

        STATE_2: begin
            // Increment N, Nm1, node 0 now ready
            mem_N_raddr   <= next_read_N;
            mem_Nm1_raddr <= next_read_Nm1;
            u_up <= mem_N_rdata;
        end

        STATE_3: begin
            // Increment N, Nm1, node 1 now ready
            mem_N_raddr   <= next_read_N;
            mem_Nm1_raddr <= next_read_Nm1;
            u_up <= mem_N_rdata;
            u_centerM1 <= mem_Nm1_rdata;
            
        end

        STATE_4: begin
            mem_N_raddr   <= next_read_N;
            mem_Nm1_raddr <= next_read_Nm1;
            u_up          <= (mem_N_raddr != COLUMN_DEPTH-1) ? mem_N_rdata : 18'sd0;
            u_center      <= u_up
            u_centerM1 <= mem_Nm1_rdata;
        end

        STATE_5: begin
            mem_N_waddr <= next_N_waddr;
            mem_Nm1_waddr <= next_Nm1_waddr; // outside init, Nm1 advances on its own write pointer so it can lag N
            mem_N_wdata <= compute_out;
            mem_Nm1_wdata <= u_center;
        end

        STATE_6: begin
           done <= 1;
        end

    endcase
end




endmodule



module M10K_COLUMN ( 
    output reg [COLUMN_DEPTH-1:0] q,
    input [COLUMN_DEPTH-1:0] d,
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
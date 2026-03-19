module full_drum #(
    parameter integer DATA_WIDTH = 18,
    parameter integer COLUMN_DEPTH = 100,
    parameter integer NUM_COLUMNS = 100,
    parameter integer PEAK_INIT = 131071,
    parameter integer ETA_SHIFT = 13
)
(
    input logic clk,
    input logic rst,
    input logic next_sample,
    input logic signed [DATA_WIDTH-1:0] rho_eff,
    input logic signed [DATA_WIDTH-1:0] G_tension,
    input logic [$clog2(COLUMN_DEPTH)-1:0] drum_length,
    output logic signed [DATA_WIDTH-1:0] center_center_node,
    output logic done,
    output logic [NUM_COLUMNS*DATA_WIDTH-1:0] all_middle_nodes,

    // Scan interface: read any row from all columns while idle
    input  logic [$clog2(COLUMN_DEPTH)-1:0] scan_addr,
    output logic [NUM_COLUMNS*DATA_WIDTH-1:0] scan_data_all
);

    localparam integer CENTER_COLUMN = (NUM_COLUMNS - 1) / 2;
    localparam integer CENTER_ROW    = (COLUMN_DEPTH - 1) / 2;
	 
	 //Rho effective calculation:

    function signed [17:0] mult_1p17;
        input signed [17:0] a;
        input signed [17:0] b;
        logic signed [35:0] mult_out;
        begin
            mult_out = a * b;
            mult_1p17 = {mult_out[35], mult_out[33:17]};
        end
    endfunction

	wire signed [DATA_WIDTH-1:0] comb_rho_eff;
     
    wire signed [DATA_WIDTH-1:0] center_node_sq = mult_1p17(center_center_node, center_center_node);
    wire signed [DATA_WIDTH-1:0] mult_term_sq =   mult_1p17(G_tension, G_tension);
    wire signed [DATA_WIDTH-1:0] rho_eff_term =   mult_1p17(mult_term_sq, center_node_sq) + 18'sd32768;
    wire signed [DATA_WIDTH-1:0] max_rho_eff = (rho_eff_term > 18'sd64225) ? 18'sd64225 : rho_eff_term; // Clamp max to 0.49

    logic signed [DATA_WIDTH-1:0] nonlinear_rho_eff;

    


    // ---- Init FSM: compute 2D pyramid and write to columns serially ----
    localparam int COL_ADDR_W = $clog2(COLUMN_DEPTH);
    logic [COL_ADDR_W-1:0] init_row;
    logic                   init_we;
    logic                   init_done_r;
    logic signed [DATA_WIDTH-1:0] init_data [NUM_COLUMNS-1:0];

    // Manhattan-distance diamond initial condition (matches Python reference):
    //   uHit[i,j] = max(0, PLUCK_RADIUS - (|x_mid - i| + |y_mid - j|)) / PLUCK_RADIUS
    // Scaled by PEAK_INIT. Only nonzero within PLUCK_RADIUS of center.
    localparam integer PLUCK_RADIUS = 64;

    genvar g;
    generate
        for (g = 0; g < NUM_COLUMNS; g++) begin : init_val_gen
            localparam integer DIST_COL_ABS = (g > CENTER_COLUMN) ? (g - CENTER_COLUMN) : (CENTER_COLUMN - g);

            wire [$clog2(COLUMN_DEPTH):0] dist_row_abs =
                (init_row > CENTER_ROW[COL_ADDR_W-1:0]) ?
                    ($clog2(COLUMN_DEPTH)+1)'(init_row - CENTER_ROW[COL_ADDR_W-1:0]) :
                    ($clog2(COLUMN_DEPTH)+1)'(CENTER_ROW[COL_ADDR_W-1:0] - init_row);

            wire [$clog2(COLUMN_DEPTH)+1:0] manhattan = ($clog2(COLUMN_DEPTH)+2)'(DIST_COL_ABS) + {1'b0, dist_row_abs};

            wire signed [35:0] height = (32'(manhattan) < 32'(PLUCK_RADIUS)) ?
                ($signed(PEAK_INIT[DATA_WIDTH-1:0]) * $signed({1'b0, (PLUCK_RADIUS[COL_ADDR_W:0] - manhattan[COL_ADDR_W:0])}))
                    / $signed(36'(PLUCK_RADIUS)) :
                36'sd0;

            // Force boundaries to zero
            wire is_boundary = (g == 0) || (g == NUM_COLUMNS - 1) ||
                               (init_row == 0) || (init_row == COL_ADDR_W'(COLUMN_DEPTH - 1));

            assign init_data[g] = is_boundary ? 18'sd0 : height[DATA_WIDTH-1:0];
        end
    endgenerate

    // Init FSM: iterate through all rows
    always_ff @(posedge clk) begin
        if (rst) begin
            init_row    <= '0;
            init_we     <= 1'b1;
            init_done_r <= 1'b0;
            nonlinear_rho_eff <= 18'sd32768; // Start with linear rho_eff for first sample
        end else if (!init_done_r) begin
            if (init_row == COL_ADDR_W'(COLUMN_DEPTH - 1)) begin
                init_we     <= 1'b0;
                init_done_r <= 1'b1;
            end else begin
                
                init_row <= init_row + 1;
            end
        end else begin
            nonlinear_rho_eff <= (next_sample) ? max_rho_eff : nonlinear_rho_eff; // Update nonlinear rho_eff at each new of the entire column
            init_we <= 1'b0;
        end
    end

    // ---- Column instances ----
    logic signed [DATA_WIDTH-1:0] u_neighbor [NUM_COLUMNS-1:0];
    logic signed [DATA_WIDTH-1:0] u_middle_node [NUM_COLUMNS-1:0];
    logic signed [DATA_WIDTH-1:0] scan_data_col [NUM_COLUMNS-1:0];
    logic [NUM_COLUMNS-1:0] done_columns;

    wire next_sample_gated = next_sample & init_done_r;

    genvar i;
    generate
        for (i = 0; i < NUM_COLUMNS; i++) begin : column_gen
            single_column_wave_equation #(
                .ETA_SHIFT(ETA_SHIFT),
                .COLUMN_DEPTH(COLUMN_DEPTH)
            ) column_inst (
                .clk(clk),
                .rst(rst),
                .rho_eff(nonlinear_rho_eff),
                .G_tension(G_tension),
                .init_data(init_data[i]),
                .init_addr(init_row),
                .init_we(init_we),
                .scan_addr(scan_addr),
                .scan_data(scan_data_col[i]),
                .u_right((i < NUM_COLUMNS - 1) ? u_neighbor[i + 1] : '0),
                .u_left((i > 0) ? u_neighbor[i - 1] : '0),
                .next_sample(next_sample_gated),
                .wave_value(u_neighbor[i]),
                .u_middle_node(u_middle_node[i]),
                .center_node_14(),
                .done(done_columns[i])
            );
        end
    endgenerate

    assign center_center_node = u_middle_node[CENTER_COLUMN];
    assign done = &done_columns;

    genvar m;
    generate
        for (m = 0; m < NUM_COLUMNS; m++) begin : pack_middle
            assign all_middle_nodes[m*DATA_WIDTH +: DATA_WIDTH] = u_middle_node[m];
        end
    endgenerate

    genvar s;
    generate
        for (s = 0; s < NUM_COLUMNS; s++) begin : pack_scan
            assign scan_data_all[s*DATA_WIDTH +: DATA_WIDTH] = scan_data_col[s];
        end
    endgenerate

endmodule

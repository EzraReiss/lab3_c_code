module multi_column_drum #(
    parameter integer DATA_WIDTH = 18,
    parameter integer COLUMN_DEPTH = 101,
    parameter integer NUM_COLUMNS = 101,
    parameter integer PEAK_INIT = 16384,
    parameter integer ETA_SHIFT = 10
)
(
    input logic clk,
    input logic rst,
    input logic next_sample,
    input logic signed [DATA_WIDTH-1:0] rho_eff,
    input logic signed [DATA_WIDTH-1:0] G_tension,
    output logic signed [DATA_WIDTH-1:0] center_center_node,
    output logic done,
    output logic [NUM_COLUMNS*DATA_WIDTH-1:0] all_middle_nodes
);

    localparam integer CENTER_COLUMN = (NUM_COLUMNS - 1) / 2;
    localparam integer CENTER_ROW    = (COLUMN_DEPTH - 1) / 2;

    // ---- Init FSM: compute 2D pyramid and write to columns serially ----
    localparam int COL_ADDR_W = $clog2(COLUMN_DEPTH);
    logic [COL_ADDR_W-1:0] init_row;
    logic                   init_we;
    logic                   init_done_r;
    logic signed [DATA_WIDTH-1:0] init_data [NUM_COLUMNS-1:0];

    // For each column c at row r, pyramid value =
    //   PEAK_INIT * min(dist_from_edge_col, dist_from_edge_row) / min(CENTER_COLUMN, CENTER_ROW)
    // where dist_from_edge_col = min(c, NUM_COLUMNS-1-c)
    //       dist_from_edge_row = min(r, COLUMN_DEPTH-1-r)
    // This gives a proper cone/pyramid that's zero on all four boundaries.

    localparam integer CENTER_MIN = (CENTER_COLUMN < CENTER_ROW) ? CENTER_COLUMN : CENTER_ROW;
    localparam integer CENTER_MIN_SAFE = (CENTER_MIN == 0) ? 1 : CENTER_MIN;

    genvar g;
    generate
        for (g = 0; g < NUM_COLUMNS; g++) begin : init_val_gen
            localparam integer DIST_COL = (g < CENTER_COLUMN) ? g : (NUM_COLUMNS - 1 - g);

            wire [COL_ADDR_W-1:0] dist_row_lo = init_row;
            wire [COL_ADDR_W-1:0] dist_row_hi = COL_ADDR_W'(COLUMN_DEPTH - 1) - init_row;
            wire [COL_ADDR_W-1:0] dist_row = (dist_row_lo < dist_row_hi) ? dist_row_lo : dist_row_hi;

            wire [COL_ADDR_W-1:0] dist_min_val = (DIST_COL[COL_ADDR_W-1:0] < dist_row) ?
                                                   DIST_COL[COL_ADDR_W-1:0] : dist_row;

            wire signed [35:0] pyramid_wide = $signed(PEAK_INIT[DATA_WIDTH-1:0]) *
                                              $signed({1'b0, dist_min_val});
            wire signed [35:0] pyramid_div  = pyramid_wide / $signed(36'(CENTER_MIN_SAFE));
            assign init_data[g] = pyramid_div[DATA_WIDTH-1:0];
        end
    endgenerate

    // Init FSM: iterate through all rows
    always_ff @(posedge clk) begin
        if (rst) begin
            init_row    <= '0;
            init_we     <= 1'b1;
            init_done_r <= 1'b0;
        end else if (!init_done_r) begin
            if (init_row == COL_ADDR_W'(COLUMN_DEPTH - 1)) begin
                init_we     <= 1'b0;
                init_done_r <= 1'b1;
            end else begin
                init_row <= init_row + 1;
            end
        end else begin
            init_we <= 1'b0;
        end
    end

    // ---- Column instances ----
    logic signed [DATA_WIDTH-1:0] u_neighbor [NUM_COLUMNS-1:0];
    logic signed [DATA_WIDTH-1:0] u_middle_node [NUM_COLUMNS-1:0];
    logic [NUM_COLUMNS-1:0] done_columns;

    // Gate next_sample until init is complete
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
                .rho_eff(rho_eff),
                .G_tension(G_tension),
                .init_data(init_data[i]),
                .init_addr(init_row),
                .init_we(init_we),
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

endmodule

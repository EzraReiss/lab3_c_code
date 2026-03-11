module multi_column_drum #(
    parameter integer DATA_WIDTH = 18,
    parameter integer COLUMN_DEPTH = 29,
    parameter integer NUM_COLUMNS = 10,
    parameter integer PEAK_INIT = 16384
)
(
    input logic clk,
    input logic rst,
    input logic next_sample,
    input logic signed [DATA_WIDTH-1:0] rho_eff,
    input logic signed [DATA_WIDTH-1:0] G_tension,
    output logic signed [DATA_WIDTH-1:0] center_center_node,
    output logic done
);

    localparam integer CENTER_COLUMN = (NUM_COLUMNS - 1) / 2;
    localparam integer COLUMN_STEP = (CENTER_COLUMN == 0) ? PEAK_INIT : (PEAK_INIT / CENTER_COLUMN);

    logic signed [DATA_WIDTH-1:0] u_neighbor [NUM_COLUMNS - 1:0];
    logic signed [DATA_WIDTH-1:0] u_middle_node [NUM_COLUMNS - 1:0];
    logic signed [DATA_WIDTH-1:0] initial_value [NUM_COLUMNS - 1:0];
    logic [NUM_COLUMNS - 1:0] done_columns;

    genvar c;
    generate
        for (c = 0; c < NUM_COLUMNS; c++) begin : init_gen
            localparam integer DIST_FROM_CENTER = (c > CENTER_COLUMN) ? (c - CENTER_COLUMN) : (CENTER_COLUMN - c);
            localparam integer HEIGHT_STEPS = (CENTER_COLUMN - DIST_FROM_CENTER < 0) ? 0 : (CENTER_COLUMN - DIST_FROM_CENTER);
            localparam integer INIT_VAL_INT = HEIGHT_STEPS * COLUMN_STEP;
            localparam logic signed [DATA_WIDTH-1:0] INIT_VAL = INIT_VAL_INT[DATA_WIDTH-1:0];
            assign initial_value[c] = INIT_VAL;
        end
    endgenerate

    genvar i;
    generate
        for (i = 0; i < NUM_COLUMNS; i++) begin : column_gen
            single_column_wave_equation #(
                .ETA_SHIFT(10),
                .COLUMN_DEPTH(COLUMN_DEPTH)
            ) column_inst (
                .clk(clk),
                .rst(rst),
                .rho_eff(rho_eff),
                .G_tension(G_tension),
                .initial_value(initial_value[i]),
                .u_right((i < NUM_COLUMNS - 1) ? u_neighbor[i + 1] : 18'sd0),
                .u_left((i > 0) ? u_neighbor[i - 1] : 18'sd0),
                .next_sample(next_sample),
                .wave_value(u_neighbor[i]),
                .u_middle_node(u_middle_node[i]),
                .center_node_14(),
                .done(done_columns[i])
            );
        end
    endgenerate

    assign center_center_node = u_middle_node[CENTER_COLUMN];
    assign done = &done_columns;

endmodule

`timescale 1ns / 1ps

module single_node_wave_equation_tb;

    // ---- timing ----
    localparam CLK_PERIOD = 20;       // 50 MHz
    localparam NUM_CYCLES = 2000;

    // ---- 1.17 fixed-point constants ----
    //  rho = 1/16  →  0.0625 * 2^17 = 8192
    //  amplitude ~1/8 full-scale  →  131072/8 = 16384
    localparam signed [17:0] RHO_VAL  = 18'sd8192;
    localparam signed [17:0] INIT_AMP = 18'sd16384;

    // ---- DUT signals ----
    logic               clk;
    logic               rst;
    logic signed [17:0] rho_eff;
    logic signed [17:0] G_tension;
    logic signed [17:0] initial_value;
    logic signed [17:0] wave_value;
    logic               done;

    // ---- instantiate DUT (column FSM) ----
    single_column_wave_equation #(
        .ETA_SHIFT (10)
    ) dut (
        .clk           (clk),
        .rst           (rst),
        .rho_eff       (rho_eff),
        .G_tension     (G_tension),
        .initial_value (initial_value),
        .wave_value    (wave_value),
        .done          (done)
    );

    // ---- clock ----
    initial clk = 0;
    always #(CLK_PERIOD/2) clk = ~clk;

    // ---- logging ----
    integer fout;

    // ---- stimulus ----
    initial begin
        fout = $fopen("wave_output.txt", "w");

        // drive constants
        rho_eff       = RHO_VAL;      // 1/16 in 1.17
        G_tension     = 18'sd0;       // unused for now
        initial_value = INIT_AMP;     // ~1/8 full-scale

        // ---- assert reset (loads triangle initial conditions into M10Ks) ----
        rst = 1'b1;
        repeat (5) @(posedge clk);
        @(negedge clk);
        rst = 1'b0;

        // ---- wait for INIT to finish, then run and record ----
        wait (done);
        @(posedge clk);
        // Re-trigger by de-asserting done (start new timestep) — 
        // for continuous operation you'd add a top-level controller here.
        for (int i = 0; i < NUM_CYCLES; i++) begin
            @(posedge clk);
            $fwrite(fout, "%0d %0d\n", i, $signed(wave_value));
            if (i < 40 || i % 100 == 0)
                $display("cycle %5d : wave_value = %7d  (0x%05h)",
                         i, $signed(wave_value), wave_value);
        end

        $fclose(fout);
        $display("");
        $display("--------------------------------------------");
        $display("  Done — %0d cycles, rho = %0d (1.17)", NUM_CYCLES, RHO_VAL);
        $display("  Output in wave_output.txt");
        $display("--------------------------------------------");
        $stop;
    end

    // ---- watchdog ----
    initial begin
        #(CLK_PERIOD * (NUM_CYCLES + 200));
        $display("TIMEOUT");
        $stop;
    end

endmodule

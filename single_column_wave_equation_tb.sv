`timescale 1ns / 1ps

module single_column_wave_equation_tb;

    localparam integer CLK_PERIOD   = 20;
    localparam integer MAX_CYCLES   = 250;
    localparam integer COLUMN_DEPTH = 29;
    localparam integer CENTER_NODE  = 15;
    localparam signed [17:0] RHO0_VAL      = 18'sd8192;
    localparam signed [17:0] RHO_EFF_MAX   = 18'sd64225; // floor(0.49 * 2^17)
    localparam signed [17:0] G_TENSION_VAL = 18'sd3277;  // about 0.025 in 1.17
    localparam signed [17:0] INIT_AMP      = 18'sd16384;
    localparam signed [17:0] STEP_INCREMENT =
        ((18'sd1 <<< 17) / ((1 <<< 3) * CENTER_NODE));

    logic clk;
    logic rst;
    logic signed [17:0] rho_eff;
    logic signed [17:0] G_tension;
    logic signed [17:0] initial_value;
    logic signed [17:0] wave_value;
    logic done;

    integer trace_file;
    integer snapshot_file;
    integer cycle_count;
    integer sweep_count;
    bit init_dumped;
    bit done_dumped;
    bit done_d;

    single_column_wave_equation #(
        .ETA_SHIFT(10)
    ) dut (
        .clk(clk),
        .rst(rst),
        .rho_eff(rho_eff),
        .G_tension(G_tension),
        .initial_value(initial_value),
        .wave_value(wave_value),
        .done(done)
    );

    function automatic signed [17:0] expected_triangle(input integer idx);
        begin
            if (idx <= CENTER_NODE) begin
                expected_triangle = idx * STEP_INCREMENT;
            end else begin
                expected_triangle = (COLUMN_DEPTH - 1 - idx) * STEP_INCREMENT;
            end
        end
    endfunction

    function automatic signed [17:0] mult_1p17;
        input signed [17:0] a;
        input signed [17:0] b;
        reg signed [35:0] product;
        begin
            product = a * b;
            mult_1p17 = {product[35], product[33:17]};
        end
    endfunction

    function automatic signed [17:0] compute_rho_eff_from_center(input signed [17:0] center_value);
        reg signed [17:0] center_times_tension;
        reg signed [17:0] nonlinear_term;
        reg signed [18:0] rho_sum;
        begin
            center_times_tension = mult_1p17(center_value, G_tension);
            nonlinear_term = mult_1p17(center_times_tension, center_times_tension);
            rho_sum = $signed(RHO0_VAL) + $signed(nonlinear_term);
            if (rho_sum > RHO_EFF_MAX) begin
                compute_rho_eff_from_center = RHO_EFF_MAX;
            end else begin
                compute_rho_eff_from_center = rho_sum[17:0];
            end
        end
    endfunction

    task automatic update_rho_eff_from_column(input integer sample_cycle);
        reg signed [17:0] center_value;
        reg signed [17:0] next_rho_eff;
        begin
            center_value = $signed(dut.mem_N.mem[CENTER_NODE]);
            next_rho_eff = compute_rho_eff_from_center(center_value);
            rho_eff = next_rho_eff;
            $display("RHO_EFF UPDATE cycle=%0d sweep=%0d center=%0d g_tension=%0d rho_eff=%0d",
                sample_cycle,
                sweep_count,
                center_value,
                G_tension,
                next_rho_eff);
        end
    endtask

    task automatic dump_column_snapshot(input integer sample_cycle);
        integer idx;
        begin
            $display("COLUMN SNAPSHOT cycle=%0d state=%0d done=%0b init_addr=%0d node_count=%0d",
                sample_cycle, dut.state, done, dut.init_addr, dut.node_count);
            for (idx = 0; idx < COLUMN_DEPTH; idx = idx + 1) begin
                $display("  node[%0d] N=%0d Nm1=%0d",
                    idx,
                    $signed(dut.mem_N.mem[idx]),
                    $signed(dut.mem_Nm1.mem[idx]));
                $fwrite(snapshot_file, "%0d,%0d,%0d,%0d\n",
                    sample_cycle,
                    idx,
                    $signed(dut.mem_N.mem[idx]),
                    $signed(dut.mem_Nm1.mem[idx]));
            end
        end
    endtask

    task automatic check_init_triangle;
        integer idx;
        integer mismatch_count;
        reg signed [17:0] expected_value;
        begin
            mismatch_count = 0;
            for (idx = 0; idx < COLUMN_DEPTH; idx = idx + 1) begin
                expected_value = expected_triangle(idx);
                if (($signed(dut.mem_N.mem[idx]) !== expected_value) ||
                    ($signed(dut.mem_Nm1.mem[idx]) !== expected_value)) begin
                    mismatch_count = mismatch_count + 1;
                    $display("INIT MISMATCH node=%0d expected=%0d N=%0d Nm1=%0d",
                        idx,
                        expected_value,
                        $signed(dut.mem_N.mem[idx]),
                        $signed(dut.mem_Nm1.mem[idx]));
                end
            end

            if (mismatch_count == 0) begin
                $display("INIT CHECK PASSED: triangle profile loaded into both BRAMs.");
            end else begin
                $display("INIT CHECK FAILED: %0d mismatches detected.", mismatch_count);
            end
        end
    endtask

    initial clk = 1'b0;
    always #(CLK_PERIOD/2) clk = ~clk;

    initial begin
        trace_file = $fopen("single_column_trace.csv", "w");
        snapshot_file = $fopen("single_column_snapshots.csv", "w");

        $fwrite(trace_file,
            "cycle,state,done,init_addr,node_count,wave_value,rho_eff,mem_N_raddr,mem_Nm1_raddr,mem_N_waddr,mem_Nm1_waddr,mem_N_we,mem_Nm1_we\n");
        $fwrite(snapshot_file, "cycle,node_idx,mem_N,mem_Nm1\n");

        rho_eff       = RHO0_VAL;
        G_tension     = G_TENSION_VAL;
        initial_value = INIT_AMP;
        rst           = 1'b1;
        cycle_count   = 0;
        sweep_count   = 0;
        init_dumped   = 1'b0;
        done_dumped   = 1'b0;
        done_d        = 1'b0;

        repeat (4) @(posedge clk);
        rst = 1'b0;

        repeat (MAX_CYCLES) begin
            @(posedge clk);

            $fwrite(trace_file, "%0d,%0d,%0b,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0b,%0b\n",
                cycle_count,
                dut.state,
                done,
                dut.init_addr,
                dut.node_count,
                $signed(wave_value),
                $signed(rho_eff),
                dut.mem_N_raddr,
                dut.mem_Nm1_raddr,
                dut.mem_N_waddr,
                dut.mem_Nm1_waddr,
                dut.mem_N_we,
                dut.mem_Nm1_we);

            if (!init_dumped && (cycle_count >= COLUMN_DEPTH + 2)) begin
                $display("--- POST-INIT COLUMN DUMP ---");
                dump_column_snapshot(cycle_count);
                check_init_triangle();
                init_dumped = 1'b1;
            end

            if (done && !done_d) begin
                update_rho_eff_from_column(cycle_count);
                sweep_count = sweep_count + 1;
            end

            if (done && !done_dumped) begin
                $display("--- DONE ASSERTED: FINAL COLUMN DUMP ---");
                dump_column_snapshot(cycle_count);
                done_dumped = 1'b1;
                repeat (5) @(posedge clk);
                $fclose(trace_file);
                $fclose(snapshot_file);
                $finish;
            end

            done_d = done;
            cycle_count = cycle_count + 1;
        end

        $display("TIMEOUT after %0d cycles", MAX_CYCLES);
        dump_column_snapshot(cycle_count);
        $fclose(trace_file);
        $fclose(snapshot_file);
        $finish;
    end

endmodule
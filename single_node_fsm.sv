// Purely combinational wave-equation node.
// State (u_curr, u_prev) is supplied from external memory
// so one instance can be time-shared across an entire column.
module single_node_wave_equation #(
    parameter integer ETA_SHIFT = 11  // eta*dt/2 = 2^{-ETA_SHIFT}
)
(
    input logic signed [17:0] rho_eff, 
    input logic signed [17:0] u_curr,   // current value from mem_N
    input logic signed [17:0] u_prev,   // previous value from mem_Nm1
    input logic signed [17:0] u_up,     // neighbor above
    input logic signed [17:0] u_down,   // neighbor below
    input logic signed [17:0] u_right,  // neighbor right (for 2D extension)
    input logic signed [17:0] u_left,   // neighbor left (for 2D extension)
    output logic signed [17:0] u_next    // result to write back to mem_N
);
    
    // Widened multiply: 18-bit × 20-bit → 38-bit, extract 1.17 result.
    // Avoids overflow when the Laplacian exceeds 18-bit range.
    wire signed [19:0] laplacian = $signed({u_up[17], u_up[17], u_up})
                                 + $signed({u_down[17], u_down[17], u_down})
                                 + $signed({u_right[17], u_right[17], u_right})
                                 + $signed({u_left[17], u_left[17], u_left})
                                 - $signed({u_curr[17], u_curr[17], u_curr}) * 4;

    wire signed [37:0] product_wide = $signed(rho_eff) * laplacian;
    wire signed [17:0] product = product_wide[34:17];

    // product + 2*u_curr - (1 - eta*dt/2)*u_prev
    wire signed [17:0] sum = product + (u_curr <<< 1) - u_prev + (u_prev >>> ETA_SHIFT);

    // [1 + eta*dt/2]^{-1} * sum  ~=  sum - (sum >>> ETA_SHIFT)
    assign u_next = sum - (sum >>> ETA_SHIFT);
endmodule

// Purely combinational wave-equation node.
// State (u_curr, u_prev) is supplied from external memory
// so one instance can be time-shared across an entire column.
module single_node_wave_equation #(
    parameter integer ETA_SHIFT = 10  // eta*dt/2 = 2^{-ETA_SHIFT}  (default 2^-10)
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
    
    // 1.17 signed fixed-point multiply
    function signed [17:0] mult_1p17;
        input signed [17:0] a;
        input signed [17:0] b;
        logic signed [35:0] mult_out;
        begin
            mult_out = a * b;
            mult_1p17 = {mult_out[35], mult_out[33:17]};
        end
    endfunction

    // rho_eff * (neighbors - 2*u_curr)  (1-D: 2 neighbors)
    wire signed [17:0] product = mult_1p17(rho_eff, u_up + u_down + u_right + u_left - (u_curr <<< 1));

    // product + 2*u_curr - (1 - eta*dt/2)*u_prev
    wire signed [17:0] sum = product + (u_curr <<< 1) - u_prev + (u_prev >>> ETA_SHIFT);

    // [1 + eta*dt/2]^{-1} * sum  ~=  sum - (sum >>> ETA_SHIFT)
    assign u_next = sum - (sum >>> ETA_SHIFT);
endmodule
module single_column_wave_equation (
    input logic clk,
    input logic rst,
    input logic signed [17:0] rho_eff, 
    input logic signed [17:0] G_tension,
    input logic signed [17:0] initial_value,
    output logic signed [17:0] wave_value
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

    
endmodule


module single_node_wave_equation #(
    parameter integer ETA_SHIFT = 10  // eta*dt/2 = 2^{-ETA_SHIFT}  (default 2^-10)
)
(
    input logic clk,
    input logic rst,
    input logic signed [17:0] rho_eff, 
    input logic signed [17:0] G_tension,
    input logic signed [17:0] initial_value,
    output logic signed [17:0] wave_value
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

    logic signed [17:0] u_curr, u_prev, u_next;

    logic signed [17:0] rho_eff_reg, G_tension_reg;


    // rho_eff * (neighbors - 4*u_curr)  — all neighbors = 0 for single node
    wire signed [17:0] product = mult_1p17(rho_eff_reg, -(u_curr <<< 2));

    // product + 2*u_curr - (1 - eta*dt/2)*u_prev
    wire signed [17:0] sum = product + (u_curr <<< 1) - u_prev + (u_prev >>> ETA_SHIFT);

    // [1 + eta*dt/2]^{-1} * sum  ~=  sum - (sum >>> ETA_SHIFT)
    wire signed [17:0] expression = sum - (sum >>> ETA_SHIFT);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            u_curr <= initial_value;
            u_prev <= initial_value;
            rho_eff_reg <= rho_eff;
            G_tension_reg <= G_tension;
        end else begin
            // Update the wave values based on the wave equation    
            u_prev <= u_curr;
            u_curr <= expression;
        end
    end

    assign wave_value = u_curr;

endmodule
$ErrorActionPreference = "Stop"

verilator --cc --exe --build --top-module multi_column_drum `
    full_drum.sv single_column_fsm.sv single_node_fsm.sv full_drum_verilator_tb.cpp `
    -CFLAGS "-std=c++17"

if (-not (Test-Path ".\obj_dir\Vmulti_column_drum.exe")) {
    throw "Expected executable .\\obj_dir\\Vmulti_column_drum.exe was not generated."
}

# Optional first argument: number of output samples
if ($args.Count -gt 0) {
    .\obj_dir\Vmulti_column_drum.exe $args[0]
} else {
    .\obj_dir\Vmulti_column_drum.exe
}

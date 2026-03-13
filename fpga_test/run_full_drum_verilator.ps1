$ErrorActionPreference = "Stop"

${scriptDir} = Split-Path -Parent $MyInvocation.MyCommand.Path
${repoRoot} = (Resolve-Path (Join-Path $scriptDir "..")).Path
${verilogDir} = Join-Path $repoRoot "DE1-SoC_Computer_15_audio_only\DE1-SoC_Computer_15_audio_only\verilog"

Push-Location $repoRoot
try {
    & verilator --cc --exe --build --top-module full_drum `
        (Join-Path $verilogDir "full_drum.sv") `
        (Join-Path $verilogDir "single_column_fsm.sv") `
        (Join-Path $verilogDir "single_node_fsm.sv") `
        (Join-Path $scriptDir "full_drum_verilator_tb.cpp") `
        -CFLAGS "-std=c++17" `
        --trace

    $exePath = Join-Path $repoRoot "obj_dir\Vfull_drum.exe"
    if (-not (Test-Path $exePath)) {
        throw "Expected executable '$exePath' was not generated."
    }

    # Optional runtime args:
    #   arg0 samples, arg1 gain, arg2 vcd(0/1), arg3 max_cycles
    if ($args.Count -gt 0) {
        & $exePath @args
    } else {
        & $exePath
    }
}
finally {
    Pop-Location
}

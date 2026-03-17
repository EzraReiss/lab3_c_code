$ErrorActionPreference = "Stop"

${scriptDir} = Split-Path -Parent $MyInvocation.MyCommand.Path
${repoRoot} = (Resolve-Path (Join-Path $scriptDir "..")).Path
${verilogDir} = Join-Path $repoRoot "DE1-SoC_Computer_15_audio_only\DE1-SoC_Computer_15_audio_only\verilog"
${fullDrumPath} = Join-Path $verilogDir "full_drum.sv"
${singleColumnPath} = Join-Path $verilogDir "single_column_fsm.sv"
${singleNodePath} = Join-Path $verilogDir "single_node_fsm.sv"

if (-not (Test-Path $fullDrumPath)) {
    throw "Expected DE1-SoC source not found: $fullDrumPath"
}
if (-not (Test-Path $singleColumnPath)) {
    throw "Expected DE1-SoC source not found: $singleColumnPath"
}
if (-not (Test-Path $singleNodePath)) {
    throw "Expected DE1-SoC source not found: $singleNodePath"
}

Write-Host "Using DE1-SoC sources:"
Write-Host "  $fullDrumPath"
Write-Host "  $singleColumnPath"
Write-Host "  $singleNodePath"

Push-Location $repoRoot
try {
    & verilator --cc --exe --build --top-module full_drum `
        $fullDrumPath `
        $singleColumnPath `
        $singleNodePath `
        (Join-Path $scriptDir "full_drum_verilator_tb.cpp") `
        -CFLAGS "-std=c++17" `
        --trace

    $exePath = Join-Path $repoRoot "obj_dir\Vfull_drum.exe"
    if (-not (Test-Path $exePath)) {
        throw "Expected executable '$exePath' was not generated."
    }

    # Optional runtime args:
    #   arg0 samples, arg1 gain, arg2 vcd(0/1), arg3 max_cycles, arg4 trace_stride, arg5 trace_samples
    if ($args.Count -gt 0) {
        & $exePath @args
    } else {
        & $exePath
    }
}
finally {
    Pop-Location
}

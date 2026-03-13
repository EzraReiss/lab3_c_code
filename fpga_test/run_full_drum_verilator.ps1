$ErrorActionPreference = "Stop"

${scriptDir} = Split-Path -Parent $MyInvocation.MyCommand.Path
${repoRoot} = (Resolve-Path (Join-Path $scriptDir "..")).Path
${fpgaSrcDir} = Join-Path $repoRoot "fpga_src"

Push-Location $repoRoot
try {
    & verilator --cc --exe --build --top-module multi_column_drum `
        (Join-Path $fpgaSrcDir "full_drum.sv") `
        (Join-Path $fpgaSrcDir "single_column.sv") `
        (Join-Path $fpgaSrcDir "single_node.sv") `
        (Join-Path $scriptDir "full_drum_verilator_tb.cpp") `
        -CFLAGS "-std=c++17"

    $exePath = Join-Path $repoRoot "obj_dir\Vmulti_column_drum.exe"
    if (-not (Test-Path $exePath)) {
        throw "Expected executable '$exePath' was not generated."
    }

    # Optional first argument: number of output samples
    if ($args.Count -gt 0) {
        & $exePath $args[0]
    } else {
        & $exePath
    }
}
finally {
    Pop-Location
}

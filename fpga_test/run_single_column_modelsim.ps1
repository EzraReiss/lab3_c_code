param(
    [int]$MaxCycles = 250,
    [int]$NumSweeps = 100,
    [switch]$RunPlotScript,
    [double]$DurationSeconds = 10.0,
    [switch]$NoOpen
)

$ErrorActionPreference = 'Stop'

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = (Resolve-Path (Join-Path $scriptDir '..')).Path
$fpgaSrcDir = Join-Path $repoRoot 'fpga_src'
Push-Location $scriptDir

try {
    $vlog = Get-Command vlog -ErrorAction Stop
    $vsim = Get-Command vsim -ErrorAction Stop

    Write-Host "Compiling single-column testbench..."
    & $vlog.Source `
        "+define+TB_MAX_CYCLES=$MaxCycles" `
        "+define+TB_NUM_SWEEPS=$NumSweeps" `
        (Join-Path $fpgaSrcDir 'single_column.sv') `
        (Join-Path $scriptDir 'single_column_wave_equation_tb.sv')
    if ($LASTEXITCODE -ne 0) {
        throw "vlog failed with exit code $LASTEXITCODE"
    }

    Write-Host "Running ModelSim..."
    & $vsim.Source -c single_column_wave_equation_tb -do "run -all; quit -f"
    if ($LASTEXITCODE -ne 0) {
        throw "vsim failed with exit code $LASTEXITCODE"
    }

    if ($RunPlotScript) {
        $pythonCmd = Get-Command python -ErrorAction SilentlyContinue
        if (-not $pythonCmd) {
            $pythonCmd = Get-Command py -ErrorAction SilentlyContinue
        }
        if (-not $pythonCmd) {
            throw "Could not find 'python' or 'py' on PATH."
        }

        Write-Host "Generating PNG from simulation trace..."
        $pythonArgs = @((Join-Path $scriptDir 'run_single_column_plot.py'), '--duration-seconds', $DurationSeconds)
        if ($NoOpen) {
            $pythonArgs += '--no-open'
        }

        & $pythonCmd.Source @pythonArgs
        if ($LASTEXITCODE -ne 0) {
            throw "Plot script failed with exit code $LASTEXITCODE"
        }
    }
}
finally {
    Pop-Location
}
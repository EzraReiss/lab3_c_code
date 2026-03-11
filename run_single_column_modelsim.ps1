param(
    [int]$MaxCycles = 250,
    [int]$NumSweeps = 100,
    [switch]$RunPlotScript,
    [double]$DurationSeconds = 10.0,
    [switch]$NoOpen
)

$ErrorActionPreference = 'Stop'

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Push-Location $scriptDir

try {
    $vlog = Get-Command vlog -ErrorAction Stop
    $vsim = Get-Command vsim -ErrorAction Stop

    Write-Host "Compiling single-column testbench..."
    & $vlog.Source "+define+TB_MAX_CYCLES=$MaxCycles" "+define+TB_NUM_SWEEPS=$NumSweeps" single_column_fsm.sv single_column_wave_equation_tb.sv
    if ($LASTEXITCODE -ne 0) {
        throw "vlog failed with exit code $LASTEXITCODE"
    }

    Write-Host "Running ModelSim..."
    & $vsim.Source -c single_column_wave_equation_tb -do "run -all; quit -f"
    if ($LASTEXITCODE -ne 0) {
        throw "vsim failed with exit code $LASTEXITCODE"
    }

    if ($RunPlotScript) {
        $python = "C:/Users/ezrar/cornell-classes/Spring 2026/ECE 5760/.venv/Scripts/python.exe"
        if (-not (Test-Path $python)) {
            throw "Expected Python environment not found at $python"
        }

        Write-Host "Generating PNG from simulation trace..."
        $pythonArgs = @('run_single_column_plot.py', '--duration-seconds', $DurationSeconds)
        if ($NoOpen) {
            $pythonArgs += '--no-open'
        }

        & $python @pythonArgs
        if ($LASTEXITCODE -ne 0) {
            throw "Plot script failed with exit code $LASTEXITCODE"
        }
    }
}
finally {
    Pop-Location
}
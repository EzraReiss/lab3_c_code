from __future__ import annotations

import argparse
import csv
import math
import os
import shutil
import subprocess
import sys
from pathlib import Path

import matplotlib
matplotlib.use("Agg")  # non-interactive backend (works in WSL without a display)
import matplotlib.pyplot as plt


WORKSPACE = Path(__file__).resolve().parent
TB_TOP = "single_column_wave_equation_tb"
SIM_OUT = WORKSPACE / "sim.vvp"
TRACE_CSV = WORKSPACE / "single_column_trace.csv"
DEFAULT_PNG = WORKSPACE / "single_column_wave_value.png"
MAX_PLOT_POINTS = 200_000

# Approximate clock cycles per column sweep:
#   STATE_0(1) + STATE_1(1) + STATE_2(1) + STATE_3(1)
#   + STATE_4(COLUMN_DEPTH) + STATE_5(1) + STATE_6(1) + next_sample latency(1)
COLUMN_DEPTH = 29
CYCLES_PER_SWEEP = COLUMN_DEPTH + 7   # ~36

SV_SOURCES = [
    "single_column_fsm.sv",
    "single_column_wave_equation_tb.sv",
]


def run_command(command: list[str], cwd: Path) -> None:
    print(f"  > {' '.join(command)}")
    completed = subprocess.run(command, cwd=cwd, text=True, capture_output=True)
    if completed.stdout:
        print(completed.stdout, end="")
    if completed.stderr:
        print(completed.stderr, end="", file=sys.stderr)
    if completed.returncode != 0:
        raise SystemExit(completed.returncode)


def compute_cycles(duration_seconds: float, clock_period_ns: float) -> int:
    return max(1, math.ceil(duration_seconds * 1e9 / clock_period_ns))


def load_trace(trace_path: Path, clock_period_ns: float) -> tuple[list[float], list[int]]:
    times: list[float] = []
    wave_values: list[int] = []

    with trace_path.open(newline="") as handle:
        reader = csv.DictReader(handle)
        for row in reader:
            cycle = int(row["cycle"])
            wave_value = int(row["wave_value"])
            times.append(cycle * clock_period_ns * 1e-9)
            wave_values.append(wave_value)

    return times, wave_values


def plot_trace(times: list[float], wave_values: list[int], png_path: Path, duration_seconds: float) -> None:
    if not times:
        raise RuntimeError("The simulation trace is empty. No plot can be generated.")

    stride = max(1, math.ceil(len(times) / MAX_PLOT_POINTS))
    sampled_times = times[::stride]
    sampled_values = wave_values[::stride]

    plt.figure(figsize=(12, 6))
    plt.plot(sampled_times, sampled_values, linewidth=1.0, color="#0b5fff")
    plt.title(f"Single-Column Wave Value vs Time ({duration_seconds:g} s request)")
    plt.xlabel("Time (s)")
    plt.ylabel("wave_value (1.17 fixed-point)")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(png_path, dpi=180)
    plt.close()


def maybe_open_png(png_path: Path, should_open: bool) -> None:
    if not should_open:
        return
    try:
        os.startfile(str(png_path))  # type: ignore[attr-defined]
    except AttributeError:
        pass


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Compile (iverilog), run (vvp), and plot the single-column wave simulation."
    )
    parser.add_argument(
        "--duration-seconds",
        type=float,
        default=10.0,
        help="Requested simulated duration in seconds. Default: 10.0",
    )
    parser.add_argument(
        "--clock-period-ns",
        type=float,
        default=20.0,
        help="Clock period used by the testbench in nanoseconds. Default: 20.0",
    )
    parser.add_argument(
        "--png",
        type=Path,
        default=DEFAULT_PNG,
        help="Output PNG path. Default: single_column_wave_value.png",
    )
    parser.add_argument(
        "--trace",
        type=Path,
        default=TRACE_CSV,
        help="Trace CSV path produced by the testbench. Default: single_column_trace.csv",
    )
    parser.add_argument(
        "--num-sweeps",
        type=int,
        default=None,
        help="Override the compile-time TB_NUM_SWEEPS value.",
    )
    parser.add_argument(
        "--no-open",
        action="store_true",
        help="Do not open the PNG after generating it.",
    )
    args = parser.parse_args()

    total_clocks = compute_cycles(args.duration_seconds, args.clock_period_ns)

    if args.num_sweeps is not None:
        num_sweeps = args.num_sweeps
    else:
        # Each column sweep takes ~CYCLES_PER_SWEEP clocks;
        # derive the number of sweeps from the requested duration.
        num_sweeps = max(1, total_clocks // CYCLES_PER_SWEEP)

    # MAX_CYCLES is a safety timeout — give enough headroom for INIT + all sweeps.
    init_overhead = COLUMN_DEPTH + 10
    max_cycles = init_overhead + num_sweeps * CYCLES_PER_SWEEP + 100

    if max_cycles > 5_000_000:
        print(
            f"Warning: {args.duration_seconds:g} s at {args.clock_period_ns:g} ns/clock is {max_cycles:,} cycles.",
            file=sys.stderr,
        )
        print(
            "This may take a while. Consider a shorter duration for interactive use.",
            file=sys.stderr,
        )

    # ---- Check for iverilog / vvp on PATH ----
    iverilog = shutil.which("iverilog")
    vvp = shutil.which("vvp")
    if iverilog is None or vvp is None:
        raise SystemExit(
            "Icarus Verilog tools 'iverilog' and 'vvp' must be on PATH.\n"
            "Install with:  apt install iverilog  (Linux)  /  brew install icarus-verilog  (macOS)\n"
            "or download from https://bleyer.org/icarus/ (Windows)"
        )

    # ---- Compile with iverilog ----
    #   -g2012    : enable SystemVerilog (IEEE 1800-2012)
    #   -D        : pass macro defines (same semantics as +define+ in commercial tools)
    #   -o sim.vvp: output compiled simulation binary
    compile_cmd = [
        iverilog,
        "-g2012",
        f"-DTB_MAX_CYCLES={max_cycles}",
        f"-DTB_NUM_SWEEPS={num_sweeps}",
        "-o", str(SIM_OUT),
        "-s", TB_TOP,
        *SV_SOURCES,
    ]
    print("Compiling…")
    run_command(compile_cmd, WORKSPACE)

    # ---- Run with vvp ----
    print("Running simulation…")
    run_command([vvp, str(SIM_OUT)], WORKSPACE)

    # ---- Load trace & plot ----
    times, wave_values = load_trace(args.trace, args.clock_period_ns)
    plot_trace(times, wave_values, args.png, args.duration_seconds)
    maybe_open_png(args.png, not args.no_open)

    print(f"Saved plot to {args.png}")
    print(f"Read {len(times):,} samples from {args.trace}")


if __name__ == "__main__":
    main()

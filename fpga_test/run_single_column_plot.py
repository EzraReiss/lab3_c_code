from __future__ import annotations

import argparse
import csv
import math
import os
import shutil
import subprocess
import sys
from pathlib import Path

import matplotlib.pyplot as plt


WORKSPACE = Path(__file__).resolve().parent
REPO_ROOT = WORKSPACE.parent
FPGA_SRC_DIR = REPO_ROOT / "fpga_src"
TB_TOP = "single_column_wave_equation_tb"
TRACE_CSV = WORKSPACE / "single_column_trace.csv"
DEFAULT_PNG = WORKSPACE / "single_column_wave_value.png"
MAX_PLOT_POINTS = 200_000
SV_FSM_SOURCE = FPGA_SRC_DIR / "single_column.sv"
SV_TB_SOURCE = WORKSPACE / "single_column_wave_equation_tb.sv"


def run_command(command: list[str], cwd: Path) -> None:
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
        os.startfile(str(png_path))
    except AttributeError:
        pass


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Compile, run, and plot the single-column wave simulation."
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

    max_cycles = compute_cycles(args.duration_seconds, args.clock_period_ns)
    num_sweeps = args.num_sweeps if args.num_sweeps is not None else max_cycles

    if max_cycles > 5_000_000:
        print(
            f"Warning: {args.duration_seconds:g} s at {args.clock_period_ns:g} ns/clock is {max_cycles:,} cycles.",
            file=sys.stderr,
        )
        print(
            "This is a very large ModelSim run and may take a long time."
            " Consider a shorter duration for interactive use.",
            file=sys.stderr,
        )

    vlog = shutil.which("vlog")
    vsim = shutil.which("vsim")
    if vlog is None or vsim is None:
        raise SystemExit("ModelSim tools 'vlog' and 'vsim' must be on PATH.")

    defines = [f"+define+TB_MAX_CYCLES={max_cycles}", f"+define+TB_NUM_SWEEPS={num_sweeps}"]
    run_command([vlog, *defines, str(SV_FSM_SOURCE), str(SV_TB_SOURCE)], WORKSPACE)
    run_command([vsim, "-c", TB_TOP, "-do", "run -all; quit -f"], WORKSPACE)

    times, wave_values = load_trace(args.trace, args.clock_period_ns)
    plot_trace(times, wave_values, args.png, args.duration_seconds)
    maybe_open_png(args.png, not args.no_open)

    print(f"Saved plot to {args.png}")
    print(f"Read {len(times):,} samples from {args.trace}")


if __name__ == "__main__":
    main()
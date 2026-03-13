#!/usr/bin/env python3
"""Plot 3D surface of drum state from binary snapshot files.

Usage:
    python plot_drum.py                           # plot init snapshot only
    python plot_drum.py drum_snapshot_init.bin     # plot specific file
    python plot_drum.py drum_snapshot_*.bin        # plot all snapshots
"""
import sys
import struct
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from pathlib import Path
import glob


def read_snapshot(filepath):
    with open(filepath, "rb") as f:
        num_columns, column_depth, sample_idx = struct.unpack("<iii", f.read(12))
        data = np.frombuffer(f.read(num_columns * column_depth * 4), dtype=np.int32)
        grid = data.reshape(column_depth, num_columns)
    return num_columns, column_depth, sample_idx, grid


def plot_snapshot(filepath, ax=None, show=True):
    num_columns, column_depth, sample_idx, grid = read_snapshot(filepath)

    # Convert from 1.17 fixed-point to float
    grid_float = grid.astype(np.float64) / 131072.0

    cols = np.arange(num_columns)
    rows = np.arange(column_depth)
    C, R = np.meshgrid(cols, rows)

    if ax is None:
        fig = plt.figure(figsize=(12, 8))
        ax = fig.add_subplot(111, projection="3d")

    surf = ax.plot_surface(C, R, grid_float, cmap="coolwarm",
                           edgecolor="none", alpha=0.9)

    label = "Initial state" if sample_idx < 0 else f"Sample {sample_idx}"
    ax.set_title(f"Drum State — {label}\n({num_columns} × {column_depth})")
    ax.set_xlabel("Column")
    ax.set_ylabel("Row")
    ax.set_zlabel("Amplitude")
    ax.figure.colorbar(surf, ax=ax, shrink=0.5, label="Amplitude (1.17)")

    if show:
        plt.tight_layout()
        plt.show()

    return ax


def main():
    if len(sys.argv) > 1:
        files = []
        for arg in sys.argv[1:]:
            files.extend(glob.glob(arg))
        files.sort()
    else:
        script_dir = Path(__file__).parent
        files = sorted(script_dir.glob("drum_snapshot_*.bin"))
        files = [str(f) for f in files]
        if not files:
            print("No drum_snapshot_*.bin files found. Run the simulation first.")
            return

    if len(files) == 1:
        plot_snapshot(files[0])
    else:
        n = len(files)
        cols = min(3, n)
        rows = (n + cols - 1) // cols
        fig = plt.figure(figsize=(6 * cols, 5 * rows))

        for idx, filepath in enumerate(files):
            num_columns, column_depth, sample_idx, grid = read_snapshot(filepath)
            grid_float = grid.astype(np.float64) / 131072.0

            col_arr = np.arange(num_columns)
            row_arr = np.arange(column_depth)
            C, R = np.meshgrid(col_arr, row_arr)

            ax = fig.add_subplot(rows, cols, idx + 1, projection="3d")
            ax.plot_surface(C, R, grid_float, cmap="coolwarm", edgecolor="none", alpha=0.9)

            label = "Initial" if sample_idx < 0 else f"Sample {sample_idx}"
            ax.set_title(label)
            ax.set_xlabel("Col")
            ax.set_ylabel("Row")
            ax.set_zlabel("Amp")

        plt.suptitle(f"Drum Evolution ({num_columns} × {column_depth})", fontsize=14)
        plt.tight_layout()
        plt.show()


if __name__ == "__main__":
    main()

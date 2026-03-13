#!/usr/bin/env bash
set -euo pipefail

# Build from a no-space temp directory because GNU Make (used by
# verilator --build) rejects directories containing spaces.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd -P)"
FPGA_SRC_DIR="$REPO_ROOT/fpga_src"
SRC_DIR="/tmp/lab3_c_code_src"

rm -rf "$SRC_DIR"
mkdir -p "$SRC_DIR"

cp "$FPGA_SRC_DIR/full_drum.sv" "$SRC_DIR/"
cp "$FPGA_SRC_DIR/single_column.sv" "$SRC_DIR/"
cp "$FPGA_SRC_DIR/single_node.sv" "$SRC_DIR/"
cp "$SCRIPT_DIR/full_drum_verilator_tb.cpp" "$SRC_DIR/"

cd "$SRC_DIR"

NUM_COLUMNS_OVERRIDE="${4:-}"
COLUMN_DEPTH_OVERRIDE="${5:-}"
VERILATOR_G_ARGS=()
if [[ -n "$NUM_COLUMNS_OVERRIDE" ]]; then
  VERILATOR_G_ARGS+=("-GNUM_COLUMNS=$NUM_COLUMNS_OVERRIDE")
fi
if [[ -n "$COLUMN_DEPTH_OVERRIDE" ]]; then
  VERILATOR_G_ARGS+=("-GCOLUMN_DEPTH=$COLUMN_DEPTH_OVERRIDE")
fi

verilator --cc --exe --build --top-module multi_column_drum \
  full_drum.sv single_column.sv single_node.sv full_drum_verilator_tb.cpp \
  -CFLAGS "-std=c++17" \
  --trace \
  "${VERILATOR_G_ARGS[@]}"

SAMPLES="${1:-96000}"
GAIN="${2:-16}"
VCD="${3:-0}"
MAX_CYCLES="${6:-100000}"
./obj_dir/Vmulti_column_drum "$SAMPLES" "$GAIN" "$VCD" "$MAX_CYCLES"

# Copy outputs back to the repository folder.
cp -f center_center_column.pcm "$SCRIPT_DIR/"
if [[ -f center_center_column.mp3 ]]; then
  cp -f center_center_column.mp3 "$SCRIPT_DIR/"
fi
if [[ -f ffmpeg.log ]]; then
  cp -f ffmpeg.log "$SCRIPT_DIR/"
fi
if [[ -f full_drum_trace.vcd ]]; then
  cp -f full_drum_trace.vcd "$SCRIPT_DIR/"
fi

echo "Done. Outputs copied to: $SCRIPT_DIR"

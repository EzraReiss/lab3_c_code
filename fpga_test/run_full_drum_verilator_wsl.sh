#!/usr/bin/env bash
set -euo pipefail

# Build from a no-space temp directory because GNU Make (used by
# verilator --build) rejects directories containing spaces.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd -P)"
VERILOG_DIR="$REPO_ROOT/DE1-SoC_Computer_15_audio_only/DE1-SoC_Computer_15_audio_only/verilog"
SRC_DIR="/tmp/lab3_c_code_src"

FULL_DRUM_PATH="$VERILOG_DIR/full_drum.sv"
SINGLE_COLUMN_PATH="$VERILOG_DIR/single_column_fsm.sv"
SINGLE_NODE_PATH="$VERILOG_DIR/single_node_fsm.sv"

[[ -f "$FULL_DRUM_PATH" ]] || { echo "Expected DE1-SoC source not found: $FULL_DRUM_PATH"; exit 1; }
[[ -f "$SINGLE_COLUMN_PATH" ]] || { echo "Expected DE1-SoC source not found: $SINGLE_COLUMN_PATH"; exit 1; }
[[ -f "$SINGLE_NODE_PATH" ]] || { echo "Expected DE1-SoC source not found: $SINGLE_NODE_PATH"; exit 1; }

echo "Using DE1-SoC sources:"
echo "  $FULL_DRUM_PATH"
echo "  $SINGLE_COLUMN_PATH"
echo "  $SINGLE_NODE_PATH"

rm -rf "$SRC_DIR"
mkdir -p "$SRC_DIR"

cp "$FULL_DRUM_PATH" "$SRC_DIR/"
cp "$SINGLE_COLUMN_PATH" "$SRC_DIR/"
cp "$SINGLE_NODE_PATH" "$SRC_DIR/"
cp "$SCRIPT_DIR/full_drum_verilator_tb.cpp" "$SRC_DIR/"

cd "$SRC_DIR"

# Args:
#   1: samples
#   2: gain
#   3: vcd (0/1)
#   4: max_cycles
#   5: trace_stride (optional, dump every N cycles)
#   6: trace_samples (optional, dump first N samples only)
#   7: NUM_COLUMNS override (optional)
#   8: COLUMN_DEPTH override (optional)
SAMPLES="${1:-96000}"
GAIN="${2:-16}"
VCD="${3:-0}"
MAX_CYCLES="${4:-100000}"
TRACE_STRIDE="${5:-256}"
TRACE_SAMPLES="${6:-8}"
NUM_COLUMNS_OVERRIDE="${7:-}"
COLUMN_DEPTH_OVERRIDE="${8:-}"

if ! [[ "$TRACE_STRIDE" =~ ^[1-9][0-9]*$ ]]; then
  echo "trace_stride must be a positive integer; got '$TRACE_STRIDE'"
  exit 1
fi

if ! [[ "$TRACE_SAMPLES" =~ ^[1-9][0-9]*$ ]]; then
  echo "trace_samples must be a positive integer; got '$TRACE_SAMPLES'"
  exit 1
fi

if [[ -n "$NUM_COLUMNS_OVERRIDE" ]] && ! [[ "$NUM_COLUMNS_OVERRIDE" =~ ^[1-9][0-9]*$ ]]; then
  echo "NUM_COLUMNS override must be a positive integer; got '$NUM_COLUMNS_OVERRIDE'"
  exit 1
fi
if [[ -n "$COLUMN_DEPTH_OVERRIDE" ]] && ! [[ "$COLUMN_DEPTH_OVERRIDE" =~ ^[1-9][0-9]*$ ]]; then
  echo "COLUMN_DEPTH override must be a positive integer; got '$COLUMN_DEPTH_OVERRIDE'"
  exit 1
fi

VERILATOR_G_ARGS=()
if [[ -n "$NUM_COLUMNS_OVERRIDE" ]]; then
  VERILATOR_G_ARGS+=("-GNUM_COLUMNS=$NUM_COLUMNS_OVERRIDE")
fi
if [[ -n "$COLUMN_DEPTH_OVERRIDE" ]]; then
  VERILATOR_G_ARGS+=("-GCOLUMN_DEPTH=$COLUMN_DEPTH_OVERRIDE")
fi

verilator --cc --exe --build --top-module full_drum \
  full_drum.sv single_column_fsm.sv single_node_fsm.sv full_drum_verilator_tb.cpp \
  -CFLAGS "-std=c++17" \
  --trace \
  "${VERILATOR_G_ARGS[@]}"

./obj_dir/Vfull_drum "$SAMPLES" "$GAIN" "$VCD" "$MAX_CYCLES" "$TRACE_STRIDE" "$TRACE_SAMPLES"

# Copy outputs back to the repository folder.
cp -f center_center_column.pcm "$SCRIPT_DIR/"
if [[ -f center_center_column.wav ]]; then
  cp -f center_center_column.wav "$SCRIPT_DIR/"
fi
if [[ -f center_center_column.mp3 ]]; then
  cp -f center_center_column.mp3 "$SCRIPT_DIR/"
fi
if [[ -f ffmpeg_wav.log ]]; then
  cp -f ffmpeg_wav.log "$SCRIPT_DIR/"
fi
if [[ -f ffmpeg_mp3.log ]]; then
  cp -f ffmpeg_mp3.log "$SCRIPT_DIR/"
fi
if [[ -f full_drum_trace.vcd ]]; then
  cp -f full_drum_trace.vcd "$SCRIPT_DIR/"
fi

echo "Done. Outputs copied to: $SCRIPT_DIR"

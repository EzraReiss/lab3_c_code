#!/usr/bin/env bash
set -euo pipefail

# Build from a no-space temp directory because GNU Make (used by
# verilator --build) rejects directories containing spaces.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
SRC_DIR="/tmp/lab3_c_code_src"

rm -rf "$SRC_DIR"
mkdir -p "$SRC_DIR"

cp "$SCRIPT_DIR/full_drum.sv" "$SRC_DIR/"
cp "$SCRIPT_DIR/single_column_fsm.sv" "$SRC_DIR/"
cp "$SCRIPT_DIR/single_node_fsm.sv" "$SRC_DIR/"
cp "$SCRIPT_DIR/full_drum_verilator_tb.cpp" "$SRC_DIR/"

cd "$SRC_DIR"

verilator --cc --exe --build --top-module multi_column_drum \
  full_drum.sv single_column_fsm.sv single_node_fsm.sv full_drum_verilator_tb.cpp \
  -CFLAGS "-std=c++17"

SAMPLES="${1:-96000}"
./obj_dir/Vmulti_column_drum "$SAMPLES"

# Copy outputs back to the repository folder.
cp -f center_center_column.pcm "$SCRIPT_DIR/"
if [[ -f center_center_column.mp3 ]]; then
  cp -f center_center_column.mp3 "$SCRIPT_DIR/"
fi
if [[ -f ffmpeg.log ]]; then
  cp -f ffmpeg.log "$SCRIPT_DIR/"
fi

echo "Done. Outputs copied to: $SCRIPT_DIR"

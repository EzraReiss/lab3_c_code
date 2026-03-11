#include "Vmulti_column_drum.h"
#include "verilated.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

static constexpr int kSampleRate = 48000;
static constexpr int kDefaultSamples = 96000;
static constexpr int kMaxCyclesPerSample = 200;

static inline int32_t sign_extend_18(uint32_t v) {
    v &= 0x3FFFFu;
    if (v & 0x20000u) {
        v |= 0xFFFC0000u;
    }
    return static_cast<int32_t>(v);
}

static void tick(Vmulti_column_drum* top, vluint64_t& sim_time) {
    top->clk = 0;
    top->eval();
    sim_time++;

    top->clk = 1;
    top->eval();
    sim_time++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    int total_samples = kDefaultSamples;
    if (argc >= 2) {
        total_samples = std::max(1, std::atoi(argv[1]));
    }

    auto* top = new Vmulti_column_drum;
    vluint64_t sim_time = 0;

    // Linear test: fixed rho_eff, no nonlinear update from center displacement.
    top->rho_eff = 32768;  // 0.25 in 1.17
    top->G_tension = 0;    // disabled
    top->next_sample = 0;
    top->rst = 1;

    for (int i = 0; i < 6; ++i) {
        tick(top, sim_time);
    }
    top->rst = 0;

    std::ofstream pcm_out("center_center_column.pcm", std::ios::binary);
    if (!pcm_out.is_open()) {
        std::cerr << "Failed to open center_center_column.pcm for writing.\n";
        delete top;
        return 1;
    }

    for (int s = 0; s < total_samples; ++s) {
        int guard = 0;
        while (!top->done && guard < kMaxCyclesPerSample) {
            tick(top, sim_time);
            guard++;
        }

        if (!top->done) {
            std::cerr << "Timeout waiting for done at sample " << s << ".\n";
            pcm_out.close();
            delete top;
            return 2;
        }

        int32_t sample18 = sign_extend_18(top->center_center_node);
        int32_t sample16 = sample18 >> 2;
        sample16 = std::clamp(sample16, -32768, 32767);
        int16_t out = static_cast<int16_t>(sample16);
        pcm_out.write(reinterpret_cast<const char*>(&out), sizeof(out));

        top->next_sample = 1;
        tick(top, sim_time);
        top->next_sample = 0;
        tick(top, sim_time);
    }

    pcm_out.close();

    std::string ffmpeg_cmd =
        "ffmpeg -y -f s16le -ar " + std::to_string(kSampleRate) +
        " -ac 1 -i center_center_column.pcm center_center_column.mp3 > ffmpeg.log 2>&1";

    int ffmpeg_rc = std::system(ffmpeg_cmd.c_str());
    if (ffmpeg_rc != 0) {
        std::cerr << "Simulation complete, but MP3 conversion failed.\n";
        std::cerr << "Install ffmpeg and run:\n";
        std::cerr << "ffmpeg -y -f s16le -ar 48000 -ac 1 -i center_center_column.pcm center_center_column.mp3\n";
    } else {
        std::cout << "Wrote center_center_column.mp3\n";
    }

    delete top;
    return 0;
}

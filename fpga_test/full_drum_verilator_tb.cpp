#include "Vfull_drum.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

static constexpr int kSampleRate = 48000;
static constexpr int kDefaultSamples = 96000;
static constexpr int kDefaultMaxCyclesPerSample = 100000;
static constexpr int kDefaultTraceStrideCycles = 256;
static constexpr int kDefaultTraceSampleCount = 8;
static constexpr int kDefaultGain = 16;
static constexpr int32_t kRho0 = 32768;       // 0.25 in 1.17
static constexpr int32_t kRhoEffMax = 64225;  // floor(0.49 * 2^17)
static constexpr int32_t kGnl = 9175;         // 0.07 in 1.17

static inline int32_t sign_extend_18(uint32_t v) {
    v &= 0x3FFFFu;
    if (v & 0x20000u) {
        v |= 0xFFFC0000u;
    }
    return static_cast<int32_t>(v);
}

static inline int32_t mult_1p17(int32_t a, int32_t b) {
    int64_t product = static_cast<int64_t>(a) * static_cast<int64_t>(b);
    return static_cast<int32_t>(product >> 17);
}

static inline int32_t compute_rho_eff_from_center(int32_t center_value) {
    int32_t center_times_g = mult_1p17(center_value, kGnl);
    int32_t nonlinear_term = mult_1p17(center_times_g, center_times_g);
    int32_t rho = kRho0 + nonlinear_term;
    if (rho > kRhoEffMax) {
        rho = kRhoEffMax;
    }
    return rho;
}

static void tick(Vfull_drum* top, vluint64_t& sim_time, VerilatedVcdC* tfp, bool dump_wave) {
    top->clk = 0;
    top->eval();
    sim_time++;

    top->clk = 1;
    top->eval();
#if VM_TRACE
    if (tfp != nullptr && dump_wave) {
        tfp->dump(sim_time);
    }
#endif
    sim_time++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    int total_samples = kDefaultSamples;
    int gain = kDefaultGain;
    bool write_vcd = false;
    int max_cycles_per_sample = kDefaultMaxCyclesPerSample;
    int trace_stride_cycles = kDefaultTraceStrideCycles;
    int trace_sample_count = kDefaultTraceSampleCount;
    if (argc >= 2) {
        total_samples = std::max(1, std::atoi(argv[1]));
    }
    if (argc >= 3) {
        gain = std::max(1, std::atoi(argv[2]));
    }
    if (argc >= 4) {
        write_vcd = (std::string(argv[3]) == "1");
    }
    if (argc >= 5) {
        max_cycles_per_sample = std::max(1, std::atoi(argv[4]));
    }
    if (argc >= 6) {
        trace_stride_cycles = std::max(1, std::atoi(argv[5]));
    }
    if (argc >= 7) {
        trace_sample_count = std::max(1, std::atoi(argv[6]));
    }

    auto* top = new Vfull_drum;
    vluint64_t sim_time = 0;

    VerilatedVcdC* tfp = nullptr;
#if VM_TRACE
    if (write_vcd) {
        Verilated::traceEverOn(true);
        tfp = new VerilatedVcdC;
        // Depth 0 keeps only top-level DUT signals and avoids tracing 100 column
        // instances and their memories.
        top->trace(tfp, 0);
        tfp->open("full_drum_trace.vcd");
    }
#endif

    // Nonlinear rho in TB: rho_eff is recomputed per finished sample from center displacement.
    top->rho_eff = kRho0;
    top->G_tension = 0;
    top->next_sample = 0;
    top->rst = 1;

    for (int i = 0; i < 6; ++i) {
        tick(top, sim_time, tfp, write_vcd);
    }
    top->rst = 0;

    std::ofstream pcm_out("center_center_column.pcm", std::ios::binary);
    if (!pcm_out.is_open()) {
        std::cerr << "Failed to open center_center_column.pcm for writing.\n";
        delete top;
        return 1;
    }

    std::ofstream center_trace_out("center_center_node_samples.csv");
    if (!center_trace_out.is_open()) {
        std::cerr << "Failed to open center_center_node_samples.csv for writing.\n";
        pcm_out.close();
        delete top;
        return 1;
    }
    center_trace_out << "sample_index,center_center_node\n";

    for (int s = 0; s < total_samples; ++s) {
        bool trace_this_sample = write_vcd && (s < trace_sample_count);
        int guard = 0;
        while (!top->done && guard < max_cycles_per_sample) {
            bool sparse_tick = ((guard % trace_stride_cycles) == 0);
            bool key_event = top->done || top->next_sample || top->rst;
            tick(top, sim_time, tfp, trace_this_sample && (sparse_tick || key_event));
            guard++;
        }

        if (!top->done) {
            std::cerr << "Timeout waiting for done at sample " << s
                      << " after " << max_cycles_per_sample << " cycles.\n";
            pcm_out.close();
            delete top;
            return 2;
        }

        int32_t sample18 = sign_extend_18(top->center_center_node);
        int32_t sample16 = (sample18 * gain) >> 2;
        sample16 = std::clamp(sample16, -32768, 32767);
        int16_t out = static_cast<int16_t>(sample16);
        pcm_out.write(reinterpret_cast<const char*>(&out), sizeof(out));
        center_trace_out << s << ',' << sample18 << '\n';

        // Update rho_eff for next sample using nonlinear center-node model.
        top->rho_eff = compute_rho_eff_from_center(sample18);

        top->next_sample = 1;
        tick(top, sim_time, tfp, trace_this_sample);
        top->next_sample = 0;
        tick(top, sim_time, tfp, trace_this_sample);
    }

    pcm_out.close();
    center_trace_out.close();

#if VM_TRACE
    if (tfp != nullptr) {
        tfp->close();
        delete tfp;
        tfp = nullptr;
    }
#endif

    std::string wav_cmd =
        "ffmpeg -y -f s16le -ar " + std::to_string(kSampleRate) +
        " -ac 1 -i center_center_column.pcm center_center_column.wav > ffmpeg_wav.log 2>&1";
    int wav_rc = std::system(wav_cmd.c_str());

    if (wav_rc != 0) {
        std::cerr << "Simulation complete, but WAV conversion failed.\n";
        std::cerr << "Install ffmpeg and run:\n";
        std::cerr << "ffmpeg -y -f s16le -ar 48000 -ac 1 -i center_center_column.pcm center_center_column.wav\n";
    } else {
        std::cout << "Wrote center_center_column.wav\n";
    }

    std::string mp3_cmd =
        "ffmpeg -y -f s16le -ar " + std::to_string(kSampleRate) +
        " -ac 1 -i center_center_column.pcm center_center_column.mp3 > ffmpeg_mp3.log 2>&1";

    int mp3_rc = std::system(mp3_cmd.c_str());
    if (mp3_rc != 0) {
        std::cerr << "Simulation complete, but MP3 conversion failed.\n";
        std::cerr << "Install ffmpeg and run:\n";
        std::cerr << "ffmpeg -y -f s16le -ar 48000 -ac 1 -i center_center_column.pcm center_center_column.mp3\n";
    } else {
        std::cout << "Wrote center_center_column.mp3\n";
    }
    std::cout << "Wrote center_center_node_samples.csv\n";

    std::cout << "Used gain=" << gain << " (arg2), vcd=" << (write_vcd ? 1 : 0)
              << " (arg3), max_cycles=" << max_cycles_per_sample << " (arg4), trace_stride="
              << trace_stride_cycles << " (arg5), trace_samples=" << trace_sample_count
              << " (arg6).\n";

    delete top;
    return 0;
}

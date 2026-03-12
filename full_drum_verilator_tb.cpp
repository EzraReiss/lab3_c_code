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
static constexpr int kDefaultMaxCyclesPerSample = 100000;
static constexpr int kDefaultGain = 16;
static constexpr int32_t kRho0 = 32768;       // 0.25 in 1.17
static constexpr int32_t kRhoEffMax = 64225;  // floor(0.49 * 2^17)
static constexpr int32_t kGnl = 9175;         // 0.07 in 1.17

// ---------------------------------------------------------------------------
// Minimal VCD writer — only dumps the 6 top-level signals we care about.
// This keeps the file small enough for Surfer/GTKWave to open without issues.
// Verilator's auto-trace at depth=1 still captures large internal arrays
// (u_neighbor[79:0], u_middle_node[79:0], etc.) which bloats the VCD file.
// ---------------------------------------------------------------------------
class MinimalVcdWriter {
    std::ofstream file_;
    bool     initialized_  = false;
    uint8_t  prev_clk_     = 0xFF;
    uint8_t  prev_rst_     = 0xFF;
    uint8_t  prev_ns_      = 0xFF;
    uint8_t  prev_done_    = 0xFF;
    uint32_t prev_center_  = 0xFFFFFFFF;
    uint32_t prev_rho_     = 0xFFFFFFFF;

    static std::string bin18(uint32_t v) {
        v &= 0x3FFFFu;
        std::string s(18, '0');
        for (int i = 0; i < 18; ++i)
            s[17 - i] = ((v >> i) & 1) ? '1' : '0';
        return s;
    }

public:
    explicit MinimalVcdWriter(const std::string& path) {
        file_.open(path);
        if (!file_.is_open()) return;
        file_ << "$timescale 1ns $end\n";
        file_ << "$scope module TOP $end\n";
        file_ << "$var wire  1 ! clk              $end\n";
        file_ << "$var wire  1 \" rst              $end\n";
        file_ << "$var wire  1 # next_sample       $end\n";
        file_ << "$var wire  1 $ done              $end\n";
        file_ << "$var wire 18 % center_center_node [17:0] $end\n";
        file_ << "$var wire 18 & rho_eff           [17:0] $end\n";
        file_ << "$upscope $end\n";
        file_ << "$enddefinitions $end\n";
    }

    bool is_open() const { return file_.is_open(); }

    void dump(uint64_t time, uint8_t clk, uint8_t rst, uint8_t next_sample,
              uint8_t done, uint32_t center, uint32_t rho) {
        if (!file_.is_open()) return;

        center &= 0x3FFFFu;
        rho    &= 0x3FFFFu;

        if (!initialized_) {
            file_ << "$dumpvars\n";
            file_ << (clk         ? "1!" : "0!") << "\n";
            file_ << (rst         ? "1\"" : "0\"") << "\n";
            file_ << (next_sample ? "1#" : "0#") << "\n";
            file_ << (done        ? "1$" : "0$") << "\n";
            file_ << "b" << bin18(center) << " %\n";
            file_ << "b" << bin18(rho)    << " &\n";
            file_ << "$end\n";
            initialized_ = true;
        } else {
            bool any = (clk != prev_clk_) || (rst != prev_rst_) ||
                       (next_sample != prev_ns_) || (done != prev_done_) ||
                       (center != (prev_center_ & 0x3FFFFu)) ||
                       (rho    != (prev_rho_    & 0x3FFFFu));
            if (!any) return;
            file_ << "#" << time << "\n";
            if (clk         != prev_clk_)  file_ << (clk         ? "1!" : "0!") << "\n";
            if (rst         != prev_rst_)  file_ << (rst         ? "1\"" : "0\"") << "\n";
            if (next_sample != prev_ns_)   file_ << (next_sample ? "1#" : "0#") << "\n";
            if (done        != prev_done_) file_ << (done        ? "1$" : "0$") << "\n";
            if (center != (prev_center_ & 0x3FFFFu)) file_ << "b" << bin18(center) << " %\n";
            if (rho    != (prev_rho_    & 0x3FFFFu)) file_ << "b" << bin18(rho)    << " &\n";
        }

        prev_clk_    = clk;
        prev_rst_    = rst;
        prev_ns_     = next_sample;
        prev_done_   = done;
        prev_center_ = center;
        prev_rho_    = rho;
    }

    void close() { file_.close(); }
};

// ---------------------------------------------------------------------------

static int  vcd_start_sample   = -1;
static int  vcd_end_sample     = -1;
static bool vcd_dumping_active = false;

static inline int32_t sign_extend_18(uint32_t v) {
    v &= 0x3FFFFu;
    if (v & 0x20000u) v |= 0xFFFC0000u;
    return static_cast<int32_t>(v);
}

static inline int32_t mult_1p17(int32_t a, int32_t b) {
    return static_cast<int32_t>((static_cast<int64_t>(a) * b) >> 17);
}

static inline int32_t compute_rho_eff_from_center(int32_t center_value) {
    int32_t cg  = mult_1p17(center_value, kGnl);
    int32_t rho = kRho0 + mult_1p17(cg, cg);
    return (rho > kRhoEffMax) ? kRhoEffMax : rho;
}

static void tick(Vmulti_column_drum* top, uint64_t& sim_time, MinimalVcdWriter* vcd) {
    top->clk = 0;
    top->eval();
    if (vcd && vcd_dumping_active)
        vcd->dump(sim_time, top->clk, top->rst, top->next_sample,
                  top->done, top->center_center_node, top->rho_eff);
    sim_time++;

    top->clk = 1;
    top->eval();
    if (vcd && vcd_dumping_active)
        vcd->dump(sim_time, top->clk, top->rst, top->next_sample,
                  top->done, top->center_center_node, top->rho_eff);
    sim_time++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    int  total_samples        = kDefaultSamples;
    int  gain                 = kDefaultGain;
    bool write_vcd            = false;
    int  max_cycles_per_sample = kDefaultMaxCyclesPerSample;

    if (argc >= 2) total_samples         = std::max(1, std::atoi(argv[1]));
    if (argc >= 3) gain                  = std::max(1, std::atoi(argv[2]));
    if (argc >= 4) write_vcd             = (std::string(argv[3]) == "1");
    if (argc >= 5) vcd_start_sample      = std::atoi(argv[4]);
    if (argc >= 6) vcd_end_sample        = std::atoi(argv[5]);
    if (argc >= 7) max_cycles_per_sample = std::max(1, std::atoi(argv[6]));

    auto* top = new Vmulti_column_drum;
    uint64_t sim_time = 0;

    MinimalVcdWriter* vcd = nullptr;
    if (write_vcd) {
        vcd = new MinimalVcdWriter("full_drum_trace.vcd");
        if (!vcd->is_open()) {
            std::cerr << "Failed to open full_drum_trace.vcd for writing.\n";
            delete vcd;
            vcd = nullptr;
        }
    }

    top->rho_eff     = kRho0;
    top->G_tension   = 0;
    top->next_sample = 0;
    top->rst         = 1;
    vcd_dumping_active = (vcd_start_sample < 0);

    for (int i = 0; i < 6; ++i)
        tick(top, sim_time, vcd);
    top->rst = 0;

    std::ofstream pcm_out("center_center_column.pcm", std::ios::binary);
    if (!pcm_out.is_open()) {
        std::cerr << "Failed to open center_center_column.pcm for writing.\n";
        delete top;
        return 1;
    }

    for (int s = 0; s < total_samples; ++s) {
        if (vcd) {
            bool in_window = (vcd_start_sample < 0) ||
                             (s >= vcd_start_sample && s < vcd_end_sample);
            vcd_dumping_active = in_window;
        }

        int guard = 0;
        while (!top->done && guard < max_cycles_per_sample) {
            tick(top, sim_time, vcd);
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
        int32_t sample16 = std::clamp((sample18 * gain) >> 2, -32768, 32767);
        int16_t out = static_cast<int16_t>(sample16);
        pcm_out.write(reinterpret_cast<const char*>(&out), sizeof(out));

        top->rho_eff = compute_rho_eff_from_center(sample18);

        top->next_sample = 1;
        tick(top, sim_time, vcd);
        top->next_sample = 0;
        tick(top, sim_time, vcd);
    }

    pcm_out.close();

    if (vcd) {
        vcd->close();
        delete vcd;
        vcd = nullptr;

        // Write a companion GTKWave save file so opening it pre-loads only
        // these signals instead of the viewer auto-expanding everything.
        std::ofstream gtkw("full_drum_trace.gtkw");
        if (gtkw.is_open()) {
            gtkw << "[dumpfile] \"full_drum_trace.vcd\"\n";
            gtkw << "[timestart] 0\n";
            gtkw << "[size] 1920 1080\n";
            gtkw << "[pos] -1 -1\n";
            gtkw << "*-23.000000 -1\n";
            gtkw << "[signal_height] 24\n";
            gtkw << "TOP.clk\n";
            gtkw << "TOP.rst\n";
            gtkw << "TOP.next_sample\n";
            gtkw << "TOP.done\n";
            gtkw << "TOP.center_center_node[17:0]\n";
            gtkw << "TOP.rho_eff[17:0]\n";
            gtkw.close();
            std::cout << "Wrote full_drum_trace.gtkw\n";
        }
        std::cout << "Wrote full_drum_trace.vcd\n";
    }

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

    std::cout << "Used gain=" << gain << " (arg2), vcd=" << (write_vcd ? 1 : 0)
              << " (arg3), vcd_start=" << vcd_start_sample
              << " (arg4), vcd_end=" << vcd_end_sample
              << " (arg5), max_cycles=" << max_cycles_per_sample << " (arg6).\n";

    delete top;
    return 0;
}

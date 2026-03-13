#include "Vmulti_column_drum.h"
#include "verilated.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static constexpr int kSampleRate = 48000;
static constexpr int kDefaultSamples = 96000;
static constexpr int kDefaultMaxCyclesPerSample = 100000;
static constexpr int kDefaultGain = 16;
static constexpr int32_t kRho0 = 32768;           // 0.25 in 1.17
static constexpr int32_t kRhoEffMax = 64225;       // floor(0.49 * 2^17)
static constexpr int32_t kDefaultGTension = 8192;  // 2^-4 = 0.0625 in 1.17

// ---------------------------------------------------------------------------
// Minimal VCD writer — dumps control signals every clock edge and all
// per-column center-node values once per audio sample (when done fires).
// ---------------------------------------------------------------------------
class MinimalVcdWriter {
    std::ofstream file_;
    int  num_columns_;
    bool initialized_ = false;

    // Previous values for change detection
    uint8_t  prev_clk_    = 0xFF;
    uint8_t  prev_rst_    = 0xFF;
    uint8_t  prev_ns_     = 0xFF;
    uint8_t  prev_done_   = 0xFF;
    uint32_t prev_rho_    = 0xFFFFFFFF;
    std::vector<uint32_t> prev_col_;

    // VCD identifier characters: '!' = 0x21, so column i gets char (0x30 + i)
    // Control signals use '!' through ')', columns start at '0' (0x30).
    static constexpr char ID_CLK  = '!';
    static constexpr char ID_RST  = '"';
    static constexpr char ID_NS   = '#';
    static constexpr char ID_DONE = '$';
    static constexpr char ID_RHO  = '%';
    static char col_id(int i) {
        // Two-char VCD identifiers: first char '0'-'~', second char '!'-'~'
        // Supports up to 94*94 = 8836 columns.
        if (i < 94) return static_cast<char>(0x30 + i);
        return static_cast<char>(0x30 + (i % 94));  // fallback
    }
    static std::string col_id_str(int i) {
        if (i < 47) {
            // Single char, offset so we don't collide with control IDs (! through %)
            return std::string(1, static_cast<char>(0x26 + i)); // '&' onwards
        }
        // Two-char IDs for i >= 47
        int adjusted = i - 47;
        char c1 = static_cast<char>('!' + (adjusted / 94));
        char c2 = static_cast<char>('!' + (adjusted % 94));
        return {c1, c2};
    }

    static std::string bin18(uint32_t v) {
        v &= 0x3FFFFu;
        std::string s(18, '0');
        for (int i = 0; i < 18; ++i)
            s[17 - i] = ((v >> i) & 1) ? '1' : '0';
        return s;
    }

public:
    MinimalVcdWriter(const std::string& path, int num_columns)
        : num_columns_(num_columns), prev_col_(num_columns, 0xFFFFFFFF)
    {
        file_.open(path);
        if (!file_.is_open()) return;

        file_ << "$timescale 1ns $end\n";
        file_ << "$scope module TOP $end\n";
        file_ << "$var wire  1 " << ID_CLK  << " clk $end\n";
        file_ << "$var wire  1 " << ID_RST  << " rst $end\n";
        file_ << "$var wire  1 " << ID_NS   << " next_sample $end\n";
        file_ << "$var wire  1 " << ID_DONE << " done $end\n";
        file_ << "$var wire 18 " << ID_RHO  << " rho_eff [17:0] $end\n";
        for (int i = 0; i < num_columns_; ++i) {
            file_ << "$var wire 18 " << col_id_str(i)
                   << " u_middle_" << i << " [17:0] $end\n";
        }
        file_ << "$upscope $end\n";
        file_ << "$enddefinitions $end\n";
    }

    bool is_open() const { return file_.is_open(); }

    // Dump control signals (called every clock edge)
    void dump_ctrl(uint64_t time, uint8_t clk, uint8_t rst,
                   uint8_t next_sample, uint8_t done, uint32_t rho) {
        if (!file_.is_open()) return;
        rho &= 0x3FFFFu;

        if (!initialized_) {
            file_ << "$dumpvars\n";
            file_ << (clk         ? '1' : '0') << ID_CLK  << "\n";
            file_ << (rst         ? '1' : '0') << ID_RST  << "\n";
            file_ << (next_sample ? '1' : '0') << ID_NS   << "\n";
            file_ << (done        ? '1' : '0') << ID_DONE << "\n";
            file_ << "b" << bin18(rho) << " " << ID_RHO << "\n";
            for (int i = 0; i < num_columns_; ++i)
                file_ << "b" << bin18(0) << " " << col_id_str(i) << "\n";
            file_ << "$end\n";
            initialized_ = true;
            prev_clk_ = clk; prev_rst_ = rst; prev_ns_ = next_sample;
            prev_done_ = done; prev_rho_ = rho;
            return;
        }

        bool any = (clk != prev_clk_) || (rst != prev_rst_) ||
                   (next_sample != prev_ns_) || (done != prev_done_) ||
                   (rho != prev_rho_);
        if (!any) return;

        file_ << "#" << time << "\n";
        if (clk         != prev_clk_)  file_ << (clk         ? '1' : '0') << ID_CLK  << "\n";
        if (rst         != prev_rst_)  file_ << (rst         ? '1' : '0') << ID_RST  << "\n";
        if (next_sample != prev_ns_)   file_ << (next_sample ? '1' : '0') << ID_NS   << "\n";
        if (done        != prev_done_) file_ << (done        ? '1' : '0') << ID_DONE << "\n";
        if (rho         != prev_rho_)  file_ << "b" << bin18(rho) << " " << ID_RHO << "\n";

        prev_clk_ = clk; prev_rst_ = rst; prev_ns_ = next_sample;
        prev_done_ = done; prev_rho_ = rho;
    }

    // Dump all column center values (called once per sample when done)
    void dump_columns(uint64_t time, const std::vector<uint32_t>& cols) {
        if (!file_.is_open() || !initialized_) return;

        bool any = false;
        for (int i = 0; i < num_columns_; ++i) {
            if ((cols[i] & 0x3FFFFu) != (prev_col_[i] & 0x3FFFFu)) { any = true; break; }
        }
        if (!any) return;

        file_ << "#" << time << "\n";
        for (int i = 0; i < num_columns_; ++i) {
            uint32_t v = cols[i] & 0x3FFFFu;
            if (v != (prev_col_[i] & 0x3FFFFu)) {
                file_ << "b" << bin18(v) << " " << col_id_str(i) << "\n";
                prev_col_[i] = v;
            }
        }
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

// rho_eff = 0.25 + (u_center * G_tension)^2
static inline int32_t compute_rho_eff(int32_t center_value, int32_t g_tension) {
    int32_t cg  = mult_1p17(center_value, g_tension);
    int32_t rho = kRho0 + mult_1p17(cg, cg);
    return (rho > kRhoEffMax) ? kRhoEffMax : rho;
}

static void tick(Vmulti_column_drum* top, uint64_t& sim_time, MinimalVcdWriter* vcd) {
    top->clk = 0;
    top->eval();
    if (vcd && vcd_dumping_active)
        vcd->dump_ctrl(sim_time, top->clk, top->rst, top->next_sample,
                       top->done, top->rho_eff);
    sim_time++;

    top->clk = 1;
    top->eval();
    if (vcd && vcd_dumping_active)
        vcd->dump_ctrl(sim_time, top->clk, top->rst, top->next_sample,
                       top->done, top->rho_eff);
    sim_time++;
}

// Extract 18-bit column values from the packed all_middle_nodes output.
// Verilator stores wide signals as arrays of uint32_t (VlWide).
static std::vector<uint32_t> extract_columns(const Vmulti_column_drum* top, int num_columns) {
    std::vector<uint32_t> cols(num_columns);
    const auto* words = reinterpret_cast<const uint32_t*>(&top->all_middle_nodes);
    for (int i = 0; i < num_columns; ++i) {
        int bit_lo = i * 18;
        int word_lo = bit_lo / 32;
        int shift   = bit_lo % 32;
        uint32_t v = words[word_lo] >> shift;
        if (shift + 18 > 32 && word_lo + 1 < static_cast<int>((num_columns * 18 + 31) / 32)) {
            v |= words[word_lo + 1] << (32 - shift);
        }
        cols[i] = v & 0x3FFFFu;
    }
    return cols;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    int     total_samples         = kDefaultSamples;
    int     gain                  = kDefaultGain;
    bool    write_vcd             = false;
    int     max_cycles_per_sample = kDefaultMaxCyclesPerSample;
    int32_t g_tension             = kDefaultGTension;

    if (argc >= 2) total_samples         = std::max(1, std::atoi(argv[1]));
    if (argc >= 3) gain                  = std::max(1, std::atoi(argv[2]));
    if (argc >= 4) write_vcd             = (std::string(argv[3]) == "1");
    if (argc >= 5) vcd_start_sample      = std::atoi(argv[4]);
    if (argc >= 6) vcd_end_sample        = std::atoi(argv[5]);
    if (argc >= 7) max_cycles_per_sample = std::max(1, std::atoi(argv[6]));
    if (argc >= 8) g_tension             = static_cast<int32_t>(std::atoi(argv[7]));

    auto* top = new Vmulti_column_drum;

    // Discover NUM_COLUMNS from the packed output width.
    // all_middle_nodes is NUM_COLUMNS*18 bits. Verilator VlWide::Words gives word count.
    // total bits = words * 32 (may include padding), but actual = NUM_COLUMNS * 18.
    // We can get it from the Verilator-generated parameter constant.
    // Use a compile-time approach: try to read the parameter via the model.
    // Verilator exposes parameters as static constexpr in the class — but the
    // easiest runtime approach is to figure it from the array size.
    int num_columns = 0;
    {
        int total_words = sizeof(top->all_middle_nodes) / sizeof(uint32_t);
        int candidate = (total_words * 32) / 18;
        while (((candidate * 18) + 31) / 32 > total_words) candidate--;
        while (((candidate + 1) * 18 + 31) / 32 <= total_words) candidate++;
        num_columns = candidate;
    }
    std::cout << "Detected NUM_COLUMNS=" << num_columns << "\n";

    uint64_t sim_time = 0;

    MinimalVcdWriter* vcd = nullptr;
    if (write_vcd) {
        vcd = new MinimalVcdWriter("full_drum_trace.vcd", num_columns);
        if (!vcd->is_open()) {
            std::cerr << "Failed to open full_drum_trace.vcd for writing.\n";
            delete vcd;
            vcd = nullptr;
        }
    }

    top->rho_eff     = kRho0;
    top->G_tension   = g_tension;
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

        // Dump all column center values once per completed sample
        if (vcd && vcd_dumping_active) {
            auto cols = extract_columns(top, num_columns);
            vcd->dump_columns(sim_time, cols);
        }

        int32_t sample18 = sign_extend_18(top->center_center_node);
        int32_t sample16 = std::clamp((sample18 * gain) >> 2, -32768, 32767);
        int16_t out = static_cast<int16_t>(sample16);
        pcm_out.write(reinterpret_cast<const char*>(&out), sizeof(out));

        top->rho_eff = compute_rho_eff(sample18, g_tension);

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
            gtkw << "TOP.rho_eff[17:0]\n";
            int center = (num_columns - 1) / 2;
            gtkw << "TOP.u_middle_" << center << "[17:0]\n";
            gtkw.close();
            std::cout << "Wrote full_drum_trace.gtkw\n";
        }
        std::cout << "Wrote full_drum_trace.vcd (with " << num_columns << " column signals)\n";
    }

    // Write WAV file directly (no ffmpeg needed)
    {
        std::ofstream wav("center_center_column.wav", std::ios::binary);
        if (wav.is_open()) {
            uint32_t data_size = total_samples * 2;
            uint32_t file_size = 36 + data_size;
            uint16_t audio_fmt = 1;
            uint16_t num_chan  = 1;
            uint32_t sr       = kSampleRate;
            uint32_t byte_rate = sr * 2;
            uint16_t block_align = 2;
            uint16_t bits      = 16;

            wav.write("RIFF", 4);
            wav.write(reinterpret_cast<const char*>(&file_size), 4);
            wav.write("WAVE", 4);
            wav.write("fmt ", 4);
            uint32_t fmt_size = 16;
            wav.write(reinterpret_cast<const char*>(&fmt_size), 4);
            wav.write(reinterpret_cast<const char*>(&audio_fmt), 2);
            wav.write(reinterpret_cast<const char*>(&num_chan), 2);
            wav.write(reinterpret_cast<const char*>(&sr), 4);
            wav.write(reinterpret_cast<const char*>(&byte_rate), 4);
            wav.write(reinterpret_cast<const char*>(&block_align), 2);
            wav.write(reinterpret_cast<const char*>(&bits), 2);
            wav.write("data", 4);
            wav.write(reinterpret_cast<const char*>(&data_size), 4);

            std::ifstream pcm_in("center_center_column.pcm", std::ios::binary);
            if (pcm_in.is_open()) {
                wav << pcm_in.rdbuf();
                pcm_in.close();
            }
            wav.close();
            std::cout << "Wrote center_center_column.wav\n";
        }
    }

    // Also convert to MP3 if ffmpeg is available
    std::string ffmpeg_cmd =
        "ffmpeg -y -f s16le -ar " + std::to_string(kSampleRate) +
        " -ac 1 -i center_center_column.pcm center_center_column.mp3 > ffmpeg.log 2>&1";

    int ffmpeg_rc = std::system(ffmpeg_cmd.c_str());
    if (ffmpeg_rc != 0) {
        std::cerr << "MP3 conversion skipped (ffmpeg not found or failed).\n";
    } else {
        std::cout << "Wrote center_center_column.mp3\n";
    }

    std::cout << "Used gain=" << gain << " (arg2), vcd=" << (write_vcd ? 1 : 0)
              << " (arg3), vcd_start=" << vcd_start_sample
              << " (arg4), vcd_end=" << vcd_end_sample
              << " (arg5), max_cycles=" << max_cycles_per_sample
              << " (arg6), g_tension=" << g_tension << " (arg7).\n";

    delete top;
    return 0;
}

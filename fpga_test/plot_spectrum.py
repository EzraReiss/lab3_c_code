#!/usr/bin/env python3
"""Power spectrum analyzer for the drum center-center node WAV output.

Usage:
    python plot_spectrum.py                              # default: center_center_column.wav
    python plot_spectrum.py center_center_column.wav     # explicit file
"""
import sys
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import wave


def read_wav(filepath):
    with wave.open(str(filepath), "rb") as wf:
        n_channels = wf.getnchannels()
        sampwidth = wf.getsampwidth()
        framerate = wf.getframerate()
        n_frames = wf.getnframes()
        raw = wf.readframes(n_frames)

    if sampwidth == 2:
        samples = np.frombuffer(raw, dtype=np.int16).astype(np.float64)
    elif sampwidth == 4:
        samples = np.frombuffer(raw, dtype=np.int32).astype(np.float64)
    else:
        raise ValueError(f"Unsupported sample width: {sampwidth}")

    if n_channels > 1:
        samples = samples[::n_channels]

    return samples, framerate


def write_wav(filepath, samples_float, sr):
    """Write normalized float samples to a 16-bit WAV."""
    peak = np.max(np.abs(samples_float))
    if peak > 0:
        scaled = np.clip(samples_float / peak * 32767, -32768, 32767).astype(np.int16)
    else:
        scaled = np.zeros(len(samples_float), dtype=np.int16)
    with wave.open(str(filepath), "wb") as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)
        wf.setframerate(sr)
        wf.writeframes(scaled.tobytes())


def lowpass_filter(samples, sr, cutoff=1000, order=5):
    """Apply a Butterworth lowpass filter."""
    try:
        from scipy.signal import butter, sosfilt
        sos = butter(order, cutoff, btype="low", fs=sr, output="sos")
        return sosfilt(sos, samples)
    except ImportError:
        # Fallback: brick-wall FFT filter
        fft = np.fft.rfft(samples)
        freqs = np.fft.rfftfreq(len(samples), d=1.0 / sr)
        fft[freqs > cutoff] = 0
        return np.fft.irfft(fft, n=len(samples))


def plot_spectrum(filepath):
    samples, sr = read_wav(filepath)
    n = len(samples)
    duration = n / sr

    samples_norm = samples / 32768.0

    # Apply 1 kHz lowpass
    samples_lp = lowpass_filter(samples_norm, sr, cutoff=1000)

    # Also write the filtered version as a WAV for listening
    lp_path = Path(filepath).parent / "center_center_column_lp1k.wav"
    write_wav(str(lp_path), samples_lp, sr)
    print(f"Wrote lowpass-filtered WAV: {lp_path}")

    fig, axes = plt.subplots(4, 1, figsize=(14, 13))

    t = np.arange(n) / sr * 1000  # ms

    # --- 1. Original Waveform ---
    axes[0].plot(t, samples_norm, linewidth=0.3, color="steelblue", alpha=0.5, label="Original")
    axes[0].plot(t, samples_lp, linewidth=0.5, color="red", label="LP 1 kHz")
    axes[0].set_xlabel("Time (ms)")
    axes[0].set_ylabel("Amplitude")
    axes[0].set_title(f"Waveform — {n} samples, {sr} Hz, {duration:.3f}s")
    axes[0].set_xlim(0, t[-1])
    axes[0].legend(loc="upper right")
    axes[0].grid(True, alpha=0.3)

    # --- 2. Power Spectrum (full range) ---
    window = np.hanning(n)

    fft_orig = np.fft.rfft(samples_norm * window)
    fft_lp = np.fft.rfft(samples_lp * window)
    freqs = np.fft.rfftfreq(n, d=1.0 / sr)
    pdb_orig = 20 * np.log10(np.abs(fft_orig) / n + 1e-12)
    pdb_lp = 20 * np.log10(np.abs(fft_lp) / n + 1e-12)

    axes[1].plot(freqs, pdb_orig, linewidth=0.4, color="steelblue", alpha=0.5, label="Original")
    axes[1].plot(freqs, pdb_lp, linewidth=0.5, color="red", label="LP 1 kHz")
    axes[1].set_xlabel("Frequency (Hz)")
    axes[1].set_ylabel("Power (dB)")
    axes[1].set_title("Power Spectrum (Full Range)")
    axes[1].set_xlim(0, sr / 2)
    axes[1].legend(loc="upper right")
    axes[1].grid(True, alpha=0.3)

    # --- 3. Power Spectrum (0–1 kHz) ---
    mask = freqs <= 1000
    axes[2].plot(freqs[mask], pdb_orig[mask], linewidth=0.5, color="steelblue", alpha=0.5, label="Original")
    axes[2].plot(freqs[mask], pdb_lp[mask], linewidth=0.5, color="red", label="LP 1 kHz")
    axes[2].set_xlabel("Frequency (Hz)")
    axes[2].set_ylabel("Power (dB)")
    axes[2].set_title("Power Spectrum (0 – 1 kHz)")
    axes[2].set_xlim(0, 1000)
    axes[2].legend(loc="upper right")
    axes[2].grid(True, alpha=0.3)

    try:
        from scipy.signal import find_peaks as _find_peaks
        peak_threshold = np.max(pdb_lp[mask]) - 20
        indices, _ = _find_peaks(pdb_lp[mask], height=peak_threshold, distance=10)
        for idx in indices[:15]:
            f = freqs[mask][idx]
            p = pdb_lp[mask][idx]
            axes[2].annotate(f"{f:.0f} Hz", (f, p), textcoords="offset points",
                             xytext=(5, 8), fontsize=7, color="red",
                             arrowprops=dict(arrowstyle="-", color="gray", lw=0.5))
    except ImportError:
        pass

    # --- 4. Spectrogram of lowpassed signal ---
    nperseg = min(1024, n // 4)
    if nperseg > 16:
        axes[3].specgram(samples_lp, NFFT=nperseg, Fs=sr, noverlap=nperseg // 2,
                         cmap="inferno", scale="dB")
        axes[3].set_xlabel("Time (s)")
        axes[3].set_ylabel("Frequency (Hz)")
        axes[3].set_title("Spectrogram (LP 1 kHz)")
        axes[3].set_ylim(0, 1000)

    fig.suptitle(Path(filepath).name, fontsize=13, fontweight="bold")
    fig.tight_layout()
    plt.show()


def main():
    if len(sys.argv) > 1:
        filepath = sys.argv[1]
    else:
        script_dir = Path(__file__).parent
        filepath = script_dir / "center_center_column.wav"
        if not filepath.exists():
            print("No center_center_column.wav found. Run the simulation first.")
            return

    plot_spectrum(str(filepath))


if __name__ == "__main__":
    main()

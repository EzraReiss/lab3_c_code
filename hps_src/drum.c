///////////////////////////////////////
/// Interactive HPS control template
/// - Configure drum row count
/// - Configure rho gain
/// - Configure initial amplitude
///
/// Replace FPGA base addresses and PIO offsets
/// with your project-specific values.
///
/// Example compile:
///   gcc drum.c -o drum -O2 -lm
///////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <math.h>

// -----------------------------------------------------------------------------
// Address map placeholders 
// -----------------------------------------------------------------------------
#define FPGA_AXI_BASE          0xC4000000
#define FPGA_AXI_SPAN          0x00001000

#define FPGA_PIO_INIT_AMP      0x00000000
#define FPGA_PIO_DONE          0x00000010
#define FPGA_PIO_NUM_ROWS      0x00000020
#define FPGA_PIO_G_TENSION     0x00000030
#define FPGA_PIO_RHO_GAIN      0x00000040

// signed 1.17 format (18-bit total, 17 fractional bits).
static inline int32_t float_to_fixed(float x) {
	const float max_1_17 = (131071.0f / 131072.0f);
	const float min_1_17 = -1.0f;
	if (x > max_1_17) x = max_1_17;
	if (x < min_1_17) x = min_1_17;
	return (int32_t)lrintf(x * 131072.0f);
}


// Drum state structure 
typedef struct {
	int rows;
	float rho_gain;
	float init_amplitude;
} DrumParams;

// Structure encapsulating FPGA interface
typedef struct {
	int fd;
	void *h2p_virtual_base;

	volatile uint32_t *pio_rows;
	volatile int32_t *pio_done;
	volatile int32_t *pio_amp;
	volatile int32_t *pio_rho_gain;
	volatile int32_t *pio_g_tension;
} FpgaIf;



// Write parameters to the FPGA
static void write_params(FpgaIf *fpga, const DrumParams *p) {
	*fpga->pio_rows = (uint32_t)p->rows;
	*fpga->pio_amp = float_to_fixed(p->init_amplitude);
	*fpga->pio_rho_gain = float_to_fixed(p->rho_gain);
	*fpga->pio_g_tension = float_to_fixed(p->g_tension);
}

static bool map_fpga(FpgaIf *fpga) {
	memset(fpga, 0, sizeof(*fpga));

	fpga->fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fpga->fd < 0) {
		perror("open /dev/mem");
		return false;
	}

	fpga->h2p_virtual_base = mmap(
		NULL,
		FPGA_AXI_SPAN,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		fpga->fd,
		FPGA_AXI_BASE
	);

	if (fpga->h2p_virtual_base == MAP_FAILED) {
		perror("mmap FPGA AXI region");
		close(fpga->fd);
		fpga->fd = -1;
		return false;
	}

	fpga->pio_rows = (volatile uint32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_NUM_ROWS);
	fpga->pio_amp  = (volatile int32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_INIT_AMP);
	fpga->pio_done = (volatile uint32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_DONE);
	fpga->pio_rho_gain = (volatile int32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_RHO_GAIN);
	fpga->pio_g_tension = (volatile int32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_G_TENSION);
	return true;
}


// Read a line of input from stdin
static bool read_line(char *buf, size_t n) {
	if (!fgets(buf, (int)n, stdin)) {
		return false;
	}
	return true;
}

static inline uint32_t done_bit(const FpgaIf *fpga) {
	return (*fpga->pio_done) & 0x1u;
}

static double elapsed_us(const struct timeval *start, const struct timeval *end) {
	int64_t sec = (int64_t)end->tv_sec - (int64_t)start->tv_sec;
	int64_t usec = (int64_t)end->tv_usec - (int64_t)start->tv_usec;
	return (double)sec * 1000000.0 + (double)usec;
}

// Measure one full done period by timing between two rising edges.
static bool measure_done_period_us(FpgaIf *fpga, double *period_us) {
	struct timeval t0, t1;

	if (!period_us) {
		return false;
	}

	// Re-sync: if currently high, wait for deassert so next high is a fresh edge.
	while (done_bit(fpga) != 0u) {
	}

	while (done_bit(fpga) == 0u) {
	}
	if (gettimeofday(&t0, NULL) != 0) {
		perror("gettimeofday");
		return false;
	}

	while (done_bit(fpga) != 0u) {
	}

	while (done_bit(fpga) == 0u) {
	}
	if (gettimeofday(&t1, NULL) != 0) {
		perror("gettimeofday");
		return false;
	}

	*period_us = elapsed_us(&t0, &t1);
	return true;
}


// Read an int from stdin
static bool prompt_int(const char *label, int *out_value) {
	char line[128];
	char *end = NULL;

	printf("%s", label);
	if (!read_line(line, sizeof(line))) {
		return false;
	}

	long v = strtol(line, &end, 10);
	if (end == line) {
		printf("Invalid integer input.\n");
		return false;
	}

	*out_value = (int)v;
	return true;
}

// read a float from stdin
static bool prompt_float(const char *label, float *out_value) {
	char line[128];
	char *end = NULL;

	printf("%s", label);
	if (!read_line(line, sizeof(line))) {
		return false;
	}

	float v = strtof(line, &end);
	if (end == line) {
		printf("Invalid float input.\n");
		return false;
	}

	*out_value = v;
	return true;
}

// Print command menu
static void print_menu(void) {
	printf("\n=== Drum Control Menu ===\n");
	printf("  p : print current parameters\n");
	printf("  n : set number of rows\n");
	printf("  a : set initial amplitude\n");
	printf("  u : update FPGA (write only)\n");
	printf("  t : measure done period (us)\n");
	printf("  r : set rho gain\n");
	printf("  g : set g tension\n");
}


// Print parameters to console
static void print_params(const DrumParams *p) {
	printf("rows=%d, init_amplitude=%f, rho_gain=%f, g_tension=%f\n",
		   p->rows,
		   p->init_amplitude,
		   p->rho_gain,
		   p->g_tension);
}

int main(void) {
    // initialize DrumParams with default values, this should sound like a wood block
	DrumParams params = {
		.rows = 30,
		.init_amplitude = 0.5f,
		.rho_gain = 0.5f,
		.g_tension = 0.5f,
	};

	FpgaIf fpga;
	if (!map_fpga(&fpga)) {
		return 1;
	}

	write_params(&fpga, &params);

	printf("Drum control started.\n");

	while (1) {
		char line[64];
		print_menu();
		printf("Enter command: ");

		if (!read_line(line, sizeof(line))) {
			clearerr(stdin);
			sleep(1);
			continue;
		}

		switch (line[0]) {
			case 'p':
				print_params(&params);
				break;

			case 'n': {
				int rows = params.rows;
				if (prompt_int("Enter number of rows: ", &rows)) {
					if (rows <= 0) {
						printf("Rows must be > 0.\n");
					} else {
						params.rows = rows;
						printf("Updated rows to %d (not written yet).\n", params.rows);
					}
				}
				break;
			}

			case 'a': {
				float amp = params.init_amplitude;
				if (prompt_float("Enter initial amplitude: ", &amp)) {
					params.init_amplitude = amp;
					printf("Updated initial amplitude to %f (not written yet).\n", params.init_amplitude);
				}
				break;
			}

			case 'u':
				write_params(&fpga, &params);
				printf("Parameters written to FPGA.\n");
				break;

			case 't': {
				double period_us = 0.0;
				if (measure_done_period_us(&fpga, &period_us)) {
					printf("Done period: %.3f us\n", period_us);
				} else {
					printf("Failed to measure done period.\n");
				}
				break;
			}

			case 'r': {
				float rho_gain = params.rho_gain;
				if (prompt_float("Enter rho gain: ", &rho_gain)) {
					params.rho_gain = rho_gain;
					printf("Updated rho gain to %f (not written yet).\n", params.rho_gain);
				}
				break;
			}

			case 'g': {
				float g_tension = params.g_tension;
				if (prompt_float("Enter g tension: ", &g_tension)) {
					params.g_tension = g_tension;
					printf("Updated g tension to %f (not written yet).\n", params.g_tension);
				}
				break;
			}

			case '\n':
				break;
			

			default:
				printf("Unknown command.\n");
				break;
		}
	}

	if (fpga.h2p_virtual_base && fpga.h2p_virtual_base != MAP_FAILED) {
		munmap(fpga.h2p_virtual_base, FPGA_AXI_SPAN);
	}
	if (fpga.fd >= 0) {
		close(fpga.fd);
	}

	return 0;
}

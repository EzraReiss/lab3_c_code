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
#include <math.h>

// -----------------------------------------------------------------------------
// Address map placeholders (TODO: REPLACE PLACEHOLDERS)
// -----------------------------------------------------------------------------
#define FPGA_AXI_BASE          0xC4000000
#define FPGA_AXI_SPAN          0x00001000

#define FPGA_PIO_NUM_ROWS      0x00000000
#define FPGA_PIO_RHO_GAIN      0x00000010
#define FPGA_PIO_INIT_AMP      0x00000020
#define FPGA_PIO_RESET         0x00000030
#define FPGA_PIO_CLK           0x00000040

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
	volatile int32_t *pio_rho;
	volatile int32_t *pio_amp;
	volatile uint32_t *pio_reset;
} FpgaIf;


// Drive the reset signal to the FPGA 
static void pulse_reset(FpgaIf *fpga) {
	*fpga->pio_reset = 1;
	usleep(10);
	*fpga->pio_reset = 0;
}

// Write parameters to the FPGA
static void write_params(FpgaIf *fpga, const DrumParams *p) {
	*fpga->pio_rows = (uint32_t)p->rows;
	*fpga->pio_rho = float_to_fixed(p->rho_gain);
	*fpga->pio_amp = float_to_fixed(p->init_amplitude);
}

// Write parameters and reset the FPGA 
static void apply_params_with_reset(FpgaIf *fpga, const DrumParams *p) {
	write_params(fpga, p);
	pulse_reset(fpga);
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
	fpga->pio_rho = (volatile int32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_RHO_GAIN);
	fpga->pio_amp = (volatile int32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_INIT_AMP);
	fpga->pio_reset = (volatile uint32_t *)((char *)fpga->h2p_virtual_base + FPGA_PIO_RESET);

	return true;
}


// Read a line of input from stdin
static bool read_line(char *buf, size_t n) {
	if (!fgets(buf, (int)n, stdin)) {
		return false;
	}
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
	printf("  r : set rho gain\n");
	printf("  a : set initial amplitude\n");
	printf("  u : update FPGA (write only)\n");
	printf("  x : update + reset drum state\n");
	printf("  q : quit\n");
}


// Print parameters to console
static void print_params(const DrumParams *p) {
	printf("rows=%d, rho_gain=%f, init_amplitude=%f\n",
		   p->rows,
		   p->rho_gain,
		   p->init_amplitude);
}

int main(void) {
    // initialize DrumParams with default values, this should sound like a wood block
	DrumParams params = {
		.rows = 30,
		.rho_gain = 0.995f,
		.init_amplitude = 0.5f,
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
			break;
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

			case 'r': {
				float rho = params.rho_gain;
				if (prompt_float("Enter rho gain: ", &rho)) {
					params.rho_gain = rho;
					printf("Updated rho gain to %f (not written yet).\n", params.rho_gain);
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

			case 'x':
				apply_params_with_reset(&fpga, &params);
				printf("Parameters written and reset pulse sent.\n");
				break;

			case 'q':
				keep_running = 0;
				break;

			case '\n':
				break;

			default:
				printf("Unknown command.\n");
				break;
		}
	}

	return 0;
}

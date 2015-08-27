#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "common.h"
#include "formats.h"


//#define LP_DOUBLE


void help(const char * cmd) {
	printf("Usage: %s bg|lp|mps m n [range] [prob]\n", cmd);
    printf("\nOptions:\n");
    printf("  -h, --help\n\tPrint short help\n");
    printf("  -s seed, --seed seed\n\tSet seed (>=0) for random generator\n");
    printf("  -r range, --range range\n\tSet range for coefficients: [-range..range] \n");
    printf("  -d density, --density density\n\tSet density (0..1] of LP\n");
	printf("  --int\n\tInteger coefficients\n");
    printf("  -o filename, --output filename\n\tSet output filename\n");
}


int help_flag = 0;
int seed = -1;			// < 0 means time()-based seed
int range = 100;		// -range ... range
float density = 0.1;	// density of matrix
int integer_flag = 0;	// integer coefficients
char * filename = 0;	// 0 means stdout
char * format = "lp";
int m = 4;
int n = 3;


struct option options[] = {
    {"help",    no_argument, &help_flag, 1},
	{"seed",	required_argument, 0, 's'},
	{"range",	required_argument, 0, 'r'},
	{"density",	required_argument, 0, 'd'},
	{"int",		no_argument, &integer_flag, 1},
	{"output",	required_argument, 0, 'o'},
	{0, 0, 0, 0}
};

#define SHORTOPT "hs:r:d:o:"


void process_args(int argc, char * argv[]) {
	// options
	while (1) {
		int option_index = 0;
		int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
		if (opt == -1) break;
		switch (opt) {
			case 'h':
				help_flag = 1;
				break;
			case 's':
				seed = atoi(optarg);
				break;
			case 'r':
				range = atoi(optarg);
				break;
			case 'd':
				density = atof(optarg);
				if (density <= 0) density = 0;
				if (density > 1) density = 1;
				break;
			case 'o':
				filename = optarg;
				break;
			case 0:
				break;
			case '?':
				error(1, "Invalid option '%c'", optopt);
			default:
				abort();
		}
	}
	// help?
	if (help_flag) {
		help(argv[0]);
		exit(0);
	}
	// arguments
	if (optind < argc) format = argv[optind++];
	if (optind < argc) m = atoi(argv[optind++]);
	if (optind < argc) n = atoi(argv[optind++]);
}


lp_t rnd() {
	return integer_flag ? rand_int(range) : rand_float(range);
}


lp_t rndsgn() {
	return integer_flag ? rand_signint(range) : rand_signfloat(range);
}


lp_t * gen_lp_0() {
	lp_t * lp = new_lp(m, n);
	lp[0] = 0;
	// generate b (first column)
	for (int i = 1; i < m; i++)
		lp[i * n] = rnd();
	// generate objective function (first row)
	for (int j = 1; j < n; j++)
		lp[j] = rand_bool_prob((int) (density * 100)) ? rndsgn() : 0;
	// generate coefficients of A
	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
			lp[i * n + j] = rand_bool_prob((int) (density * 100)) ? rndsgn() : 0;
	return lp;
}


lp_t * gen_lp_1() {
	lp_t * lp = new_lp_zero(m, n);

	// generate b (first column): all positive
	for (int i = 1; i < m; i++) lp[i * n] = rnd();

	// generate c (first row): all positive
	for (int j = 1; j < n; j++) lp[j] = rnd();

 	// count of non zero elements
	int count = (m - 1) * (n - 1) * density;

	// in each ROW: generate EXACTLY TWO positive elements
	for (int i = 1; i < m; i++) {
		for (int c = 2; c > 0;) {
			lp_t * p = &lp[i * n + rand_range(n - 1) + 1];
			if (*p == 0) { *p = rnd(); c--; count--; }
		}
	}

	// in each COLUMN: ensure one element
	for (int j = 1; j < n; j++) {
		lp_t * p = &lp[rand_range(m) * n + j];
		if (*p == 0) { *p = rndsgn(); count--; }
	}

	// fill in the rest of the matrix
	if (density == 1) {
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
				lp[i * n + j] = rndsgn();
	} else {
		while (count > 0) {
			lp_t * p = &lp[(rand_range(m - 1) + 1) * n + rand_range(n - 1) + 1];
			if (*p == 0) { *p = rndsgn(); count--; }
		}
	}

	// explicitly set
	lp[0] = 0;
	return lp;
}


int main(int argc, char * argv[]) {
	process_args(argc, argv);
	rand_init(seed);

	if (integer_flag) set_precision(0);
	lp_t * lp = gen_lp_1();

	FILE * fp = stdout;
	if (filename != 0 && !(fp = fopen(filename, "w")))
		error(2, "Cannot open file '%s'\n", filename);

	if (strcmp("bg", format) == 0) write_bg(fp, m, n, lp);
	else if (strcmp("lp", format) == 0) write_lpsolve(fp, m, n, lp);
	else error(1, "Invalid format: '%s'", format);

	if (filename != 0) fclose(fp);
	return 0;
}

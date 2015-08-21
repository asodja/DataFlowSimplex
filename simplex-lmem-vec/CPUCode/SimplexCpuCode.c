#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#include <math.h>

#include "common.h"
#include "formats.h"

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"


void help(const char * cmd) {
    printf("Usage: %s [filename]\n", cmd);
    printf("\nOptions:\n");
    printf("  -h, --help\n\tPrint short help\n");
    printf("  -i filename, --input filename\n\tSet input filename\n");
    printf("  -t level, --trace level\n\tTrace level: 0,1,7,8,9\n");
    printf("  -p rule, --pivot rule\n\tPivot selection rule: 0-first positive, 1-max positive (default)\n");
    printf("  --iter max\n\tMaximum number of iterations: 0-infinity\n");
    printf("  --info\n\tPrint basic information (todo)\n");
}


void info() {
    printf("Simplex LP solver\n");
    printf("STREAM_FREQUENCY: %d\n", Simplex_STREAM_FREQUENCY);
    printf("LMEM_FREQUENCY: %s\n", Simplex_LMEM_FREQUENCY);
	printf("FMEM_DEPTH: %d\n", Simplex_FMEM_DEPTH);
    printf("VECTOR_DEPTH: %d\n", Simplex_VECTOR_DEPTH);
}


// show help
int help_flag = 0;

// info flag
int info_flag = 0;

// Filename for loading the lp program
char * filename = 0;

/* Trace levels (higher includes lower):
	0 - print only final result
	1 - print iterations/pivoting
	2 - print c (objective function) after each iteration
    3 - print c & b (objective function & bounds) after each iteration
	7 - print input lp
	8 - print final lp
	9 - print lp during algoritm
*/
int trace = 0;

/* Pivot rules (nonnegative column):
	0 - select first
	1 - select max
*/
int pivot_rule = 1;

/* Maximum iteration count
    0 - infinity
*/
unsigned int max_iterations = 10000;


struct option options[] = {
    {"help",    no_argument, &help_flag, 1},
	{"trace",	required_argument, 0, 't'},
	{"pivot",	required_argument, 0, 'p'},
	{"input",	required_argument, 0, 'i'},
    {"iter",    required_argument, 0, 1000},
    {"info",    no_argument, &info_flag, 1},
	{0, 0, 0, 0}
};

#define SHORTOPT "ht:p:i:"


void parse_args(int argc, char * argv[]) {
	// options
	while (1) {
		int option_index = 0;
		int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
		if (opt == -1) break;
		switch (opt) {
			case 'h':
				help_flag = 1;
				break;
			case 't':
				trace = atoi(optarg);
				break;
			case 'p':
				pivot_rule = atoi(optarg);
				break;
			case 'i':
				filename = optarg;
				break;
            case 1000:
                max_iterations = atoi(optarg);
                break;
            case 0:
                break;
			case '?':
				error(1, "Invalid option '%c'", optopt);
			default:
				abort();
		}
	}
    // filename as the first arguments
    if (optind < argc) filename = argv[optind++];
	// help?
	if (help_flag) {
		help(argv[0]);
		exit(0);
	}
    if (info_flag) {
        info();
        exit(0);
    }
}


#include "simplex_dfe.c"


int main(int argc, char * argv[]) {
	// parse command line arguments
	parse_args(argc, argv);
	filename = "/home/demo/Desktop/DataFlow/simplex/lps/2048x2048-d1-s0.bg";
//	filename = "/home/demo/Desktop/DataFlow/simplex/lps/1024x1024-d1-s4.bg";
	filename = "/home/demo/Desktop/DataFlow/simplex/lps/32x32-d1-s0.bg";
	//filename = "/home/demo/Desktop/DataFlow/simplex/lps/opt145.bg";
	trace = 2;
	// read lp
	int m, n;
	lp_t * p = read_bg_filename(filename, &m, &n);
	if (trace >= 7) write_bg(stdout, m, n, p);
	// solve lp
    timing_t timer;
    timer_start(&timer);
	unsigned int count = simplex(m, n, p);
    timer_stop(&timer);
    // print results
    if (trace == 8) write_bg(stdout, m, n, p);
    printf("%d %d %"lp_t_fmt1" %d %ld %ld\n", m, n, -p[0], count, timer.realtime, timer.cputime);
	return 0;
}

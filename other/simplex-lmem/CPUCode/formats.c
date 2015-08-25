#include <stdlib.h>
#include <stdio.h>

#include "formats.h"
#include "common.h"


// private: macros for reading/printing lp_t
#define _lp_scan "%"lp_t_fmt1
#define _lp_bg_out "%.2"lp_t_fmt2
#define _lp_lpsolve_out "%+.2"lp_t_fmt2
#define _lp_lpsolve_out_var _lp_lpsolve_out" x%d "


lp_t * new_lp(const int m, const int n) {
	return (lp_t *) malloc(m * n * sizeof(lp_t));
}


lp_t * new_lp_zero(const int m, const int n) {
	return (lp_t *) calloc(m * n * sizeof(lp_t), 1);
}


void free_lp(lp_t * lp) {
	free(lp);
}


void write_bg(FILE * fp, const int m, const int n, const lp_t * lp) {
	fprintf(fp, "%i %i\n", m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(fp, _lp_bg_out, lp[i * n + j]);
			fputc(j < n - 1 ? ' ' : '\n', fp);
		}
	}
}


lp_t * read_bg(FILE * fp, int * m, int * n) {
	// read m, n
	int err = fscanf(fp, "%d %d", m, n);
  	if (err == 0 || err == EOF)
  		error(2, "Cannot read m or n\n");
  	// malloc
  	lp_t * lp = new_lp(*m, *n);
  	// read lp
  	for (int i = 0; i < *m; i++)
    	for(int j = 0; j < *n; j++) {
      	err = fscanf(fp, _lp_scan, &lp[i * *n + j]);
	    if (err == 0 || err == EOF)
	    	error(2, "Cannot read p[%d, %d]\n", i, j);
	}
    return lp;
}


lp_t * read_bg_filename(const char * filename, int * m, int * n) {
	FILE * fp = stdin;
	if (filename != 0 && !(fp = fopen(filename, "r")))
		error(2, "Cannot open file '%s'\n", filename);
	lp_t * lp = read_bg(fp, m, n);
	if (filename != 0) fclose(fp);
	return lp;
}


void write_lpsolve(FILE * fp, const int m, const int n, const lp_t * lp) {
	// objective function
	for (int j = 1; j < n; j++)
		if (lp[j] != 0) fprintf(fp, _lp_lpsolve_out_var, lp[j], j);
	fprintf(fp, ";\n");
	// constraints
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			lp_t a = lp[i * n + j];
			if (a != 0) fprintf(fp, _lp_lpsolve_out_var, a, j);
		}
		fprintf(fp, "<= "_lp_lpsolve_out" ;\n", lp[i * n]);
	}
}


void print_row(const char * msg, const int n, const lp_t * lp, const int row) {
	printf("%s", msg);
	for (int j = 0; j < n; j++) printf("%.10"lp_t_fmt2" ", lp[row * n + j]);
	putchar('\n');
}


void print_obj(const int n, const lp_t * lp) {
	print_row("obj: ", n, lp, 0);
}


void print_col(const char * msg, const int m, const int n, const lp_t * lp, const int col) {
	printf("%s", msg);
	for (int i = 0; i < m; i++) printf("%"lp_t_fmt1" ", lp[i * n + col]);
	putchar('\n');
}


void print_bounds(const int m, const int n, const lp_t * lp) {
	print_col("bnd: ", m, n, lp, 0);
}

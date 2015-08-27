#ifndef FORMATS_H
#define FORMATS_H


#ifdef LP_DOUBLE
#define lp_t double
#define lp_t_fmt1 "lg"
#define lp_t_fmt2 "lf"
#else
#define lp_t float
#define lp_t_fmt1 "g"
#define lp_t_fmt2 "f"
#endif


// LP representation
lp_t * new_lp(const int m, const int n);
lp_t * new_lp_zero(const int m, const int n);
void free_lp(lp_t * lp);

// precision after decimal point
void set_precision(const int digits);

// Belgrade format
void write_bg(FILE * fp, const int m, const int n, const lp_t * lp);
lp_t * read_bg(FILE * fp, int * m, int * n);
lp_t * read_bg_filename(const char * filename, int * m, int * n);

// lpsolve format
void write_lpsolve(FILE * fp, const int m, const int n, const lp_t * lp);

// printing lp rows/cols
void print_row(const char * msg, const int n, const lp_t * lp, const int row);
void print_obj(const int n, const lp_t * lp);
void print_col(const char * msg, const int m, const int n, const lp_t * lp, const int col);
void print_bounds(const int m, const int n, const lp_t * lp);


#endif

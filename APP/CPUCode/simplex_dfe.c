#define ALIGN_BURST		384
#define ALIGN_STREAM	16


int calc_align(int size, int align) {
	return size / align * align + (size % align > 0) * align;
}


lp_t * copy_aligned(const int m, const int n, const lp_t * p, int * align_m, int * align_n) {
	*align_m = calc_align(m, ALIGN_BURST / sizeof(lp_t));
	*align_n = calc_align(n, ALIGN_BURST / sizeof(lp_t));

	lp_t * ap = (lp_t*)malloc(*align_m * *align_n * sizeof(lp_t));
	for (int i = 0; i < *align_m; i++)
	for (int j = 0; j < *align_n; j++)
      {
        ap[i * *align_n + j] = (i < m && j < n) ? p[i * n + j] : 0;
      }
  return ap;
}


int find_pivot_column_first(const int n, const lp_t * p) {
  	for (int i = 1; i < n; i++)
  		if (p[i] > 0) return i;
  	return -1;
}


int find_pivot_column_max(const int n, const lp_t * p) {
  	int col = 1;
  	lp_t max = p[1];
  	for (int i = 2; i < n; i++)
  		if (p[i] > max) {
  			max = p[i];
  			col = i;
  		}
  	if (max <= 0) return -1;
  	return col;
}


// find a row with the smallest positive ratio = p[i, 0] / p[i, col]
int find_pivot_row1(const int m, const lp_t * b, const lp_t * pivcol) {
	int row = -1;
	lp_t minr = 0;
	for (int i = 1; i < m; i++) {
        lp_t r = b[i] / pivcol[i];
		if (r > 0 && (r < minr || row < 0)) {
			minr = r;
			row = i;
		}
	}
  	return row;
}


// find a row with the smallest positive ratio = p[i, 0] / p[i, col]
int find_pivot_row(const int m, const lp_t * ratio) {
	int row = -1;
	lp_t minr = 0;
	for (int i = 1; i < m; i++) {
        lp_t r = ratio[i];
		if (r > 0 && (r < minr || row < 0)) {
			minr = r;
			row = i;
		}
	}
  	return row;
}


static const char const *err_tag = "Error!!!";
static void raise_error(const char *msg)
{
	fprintf(stderr, "%s: %s\n", err_tag, msg);
	fflush (stderr);
}


static void check_errors(max_errors_t *errors)
{
	// If there are any errors, write them to stderr stream for the GUI to handle
	if (!max_ok(errors)) {
		char *trace = max_errors_trace(errors);
		raise_error(trace);
		free(trace);
	}
}


unsigned int simplex(const int m, const int n, lp_t * p) {
    // init DFE
    max_file_t * maxfile = Simplex_init();
	max_engine_t * engine = max_load(maxfile, "*");
	// align for streaming
	int align_m, align_n;
	lp_t * align_p = copy_aligned(m, n, p, &align_m, &align_n);
	if (trace > 0) printf("aligned: %dx%d -> %dx%d\n", m, n, align_m, align_n);
	// reserve buffers
	lp_t * c = malloc(align_n * sizeof(lp_t));
	lp_t * ratio = malloc(align_m * sizeof(lp_t));
	lp_t * pivcol = malloc(align_m * sizeof(lp_t));
	lp_t * pivrow = malloc(align_n * sizeof(lp_t));
	// init buffers: c, ratio, pivcol, pivrow
	for (int j = 0; j < n; j++) c[j] = p[j];
	uint64_t col = find_pivot_column_max(n, c);
	for (int i = 0; i < align_m; ++i) {
		pivcol[i] = align_p[i * align_n + col];
		ratio[i] = align_p[i * align_n] / pivcol[i];
	}
	int row = find_pivot_row(m, ratio);
	for (int i = 0; i < align_n; i++) pivrow[i] = align_p[row * align_n + i];
	// WriteRows - write whole tableau to lmem
    Simplex_WriteRows_actions_t writeRows;
    writeRows.param_start = 0;
    writeRows.param_rowlen = align_n;
    writeRows.param_count = align_m;
    writeRows.instream_rows_tolmem = align_p;
    Simplex_WriteRows_run(engine, &writeRows);
    // ReadRows action initialization
    Simplex_ReadRows_actions_t readRows;
    readRows.param_start = 0; // to be filled later
    readRows.param_rowlen = align_n;
    readRows.param_count = 1;
    readRows.outstream_rows_fromlmem = pivrow;
	// simplex action to call DFE
	Simplex_actions_t act;
	act.param_m = align_m;
	act.param_n = align_n;
	act.instream_pivot_col = pivcol;
	act.instream_pivot_row = pivrow;
	act.outscalar_MaxKernel_maxcol_out = &col;
	act.outstream_ratio_out = ratio;
	act.outstream_pivcol_out = pivcol;
	act.outstream_cost = c;

	// main loop
	unsigned int count = 0;
	while (count < max_iterations || max_iterations == 0) {
		// read pivot row from lmem
	    readRows.param_start = row;
	    Simplex_ReadRows_run(engine, &readRows);
	    // pivoting,max,filter
	    count++;
		lp_t pivot = pivrow[col];
	    if (trace > 0) printf("%u: pivoting on %d, %lu: %g\n", count, row, col, pivot);
	    act.param_pivot = 1 / pivot;
	    act.param_col = col;
	    act.param_row = row;
		Simplex_run(engine, &act);
		ratio[0] = -1;
		pivcol[0] = c[col];
		/*print_row("c: ", n, c, 0);
		print_row("ratio: ", m, ratio, 0);
		print_row("pivcol: ", m, pivcol, 0);*/
	    //if (trace >= 9) write_bg(stdout, m, n, p);
		if (col <= 0) break; // optimum found
		// row
		row = find_pivot_row(m, ratio);
		if (row < 0) { p[0] = NAN; break; }	// unbounded
    }

	// unload DFE
	max_unload(engine);
	// return results (TODO: copy full lp from lmem to p)
	p[0] = c[0];
	// free buffers
	free(c);
	free(ratio);
	free(pivcol);
	free(pivrow);
	return count;
}

#define ALIGN_STREAM	16


int calc_align(int size, int align) {
	return size / align * align + (size % align > 0) * align;
}


lp_t * copy_aligned(const int m, const int n, const lp_t * p, int * align_m, int * align_n) {
	int perBlock = ALIGN_STREAM / sizeof(lp_t);
	*align_m = calc_align(m, perBlock);
	*align_n = calc_align(n, perBlock);

	lp_t * align_p = (lp_t*) malloc(*align_m * *align_n * sizeof(lp_t));
	for (int i = 0; i < *align_m; i++)
		for (int j = 0; j < *align_n; j++)
			align_p[i * *align_n + j] = (i < m && j < n) ? p[i * n + j] : 0;
	return align_p;
}


inline int find_pivot_column_first(const int n, const lp_t * p) {
  	for (int i = 1; i < n; i++)
  		if (p[i] > 0) return i;
  	return -1;
}


inline int find_pivot_column_max(const int n, const lp_t * p) {
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


// find a row with the smallest positive ratio = p[i, 0] / p[i, pivot]
int find_pivot_row(const int m, const int n, const lp_t * p, int col) {
	int row = -1;
	lp_t minr = 0;
    int in = n;
	for (int i = 1; i < m; i++, in += n) {
        lp_t r = p[in] / p[in + col];
		if (r > 0 && (r < minr || row < 0)) {
			minr = r;
			row = i;
		}
	}
  	return row;
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
	lp_t * pivcol = (lp_t *) malloc(align_m * sizeof(lp_t));
	lp_t * pivrow = (lp_t *) malloc(align_n * sizeof(lp_t));
	// Simplex action to call DFE
	Simplex_actions_t act;
	act.param_m = align_m;
	act.param_n = align_n;
	act.instream_pivcol = pivcol;
	act.instream_pivrow = pivrow;
	act.instream_x = align_p;
	act.outstream_y = align_p;
	// main loop
	unsigned int count = 0;
	while (count < max_iterations || max_iterations == 0) {
		// column
		int col = pivot_rule == 0 ? find_pivot_column_first(align_n, align_p) : find_pivot_column_max(align_n, align_p);
		if (col < 0) break;	// optimum found
		// row
		int row = find_pivot_row(align_m, align_n, align_p, col);
		if (row < 0) { align_p[0] = NAN; break; }	// unbounded
		// pivoting
		count++;
		lp_t pivot = align_p[row * align_n + col];
		if (trace > 0) printf("%d: pivoting on %d, %d: %"lp_t_fmt1"\n", count, row, col, pivot);
		// store pivcol & pivrow for DFE streaming
		for (int i = 0; i < align_m; i++) pivcol[i] = align_p[i * align_n + col];
		for (int j = 0; j < align_n; j++) pivrow[j] = align_p[row * align_n + j];
		// call DFE for pivoting
		act.param_row = row;
		act.param_col = col;
		act.param_pivot = 1 / pivot;
		Simplex_run(engine, &act);
        // tracing
		if (trace >= 9) write_bg(stdout, m, n, p);
		if (trace >= 2) print_obj(n, p);
        if (trace >= 3) print_bounds(m, n, p);
	}
	// unload DFE
	max_unload(engine);
	// free buffers
	free(pivcol);
	free(pivrow);
	p[0] = align_p[0];
	return count;
}

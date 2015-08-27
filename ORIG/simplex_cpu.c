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
int find_pivot_row(const int m, const int n, const lp_t * p, int col) {
	int row = -1;
	lp_t minr;
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


void pivot_on(const int m, const int n, lp_t * p, const int row, const int col) {
    int rown = row * n;
	lp_t pivotinv = 1 / p[rown + col];
	// all others
    int in = 0;
	for (int i = 0; i < m; i++, in += n) {
		if (i == row) continue;
		lp_t p_i_col = p[in + col] * pivotinv;
		for (int j = 0; j < n; j++) {
			if (j == col) continue;
			p[in + j] -= p_i_col * p[rown + j];
		}
	}
	// change pivot row
	for (int j = 0; j < n; j++) p[rown + j] *= pivotinv;
	// change pivot col
	for (int i = 0; i < m * n; i += n) p[i + col] *= -pivotinv;
	// pivot = 1 / pivot
	p[rown + col] = pivotinv;
}


unsigned int simplex(const int m, const int n, lp_t * p) {
	unsigned int count = 0;
	while (count < max_iterations || max_iterations == 0) {
		// column
		int col = pivot_rule == 0 ? find_pivot_column_first(n, p) : find_pivot_column_max(n, p);
		if (col < 0) break;	// optimum found
		// row
		int row = find_pivot_row(m, n, p, col);
		if (row < 0) { p[0] = NAN; break; }	// unbounded
		// pivoting
        count++;
		if (trace > 0) printf("%d: pivoting on %d, %d: %"lp_t_fmt1"\n", count, row, col, p[row * n + col]);
		pivot_on(m, n, p, row, col);
        // tracing
		if (trace >= 9) write_bg(stdout, m, n, p);
		if (trace >= 2) print_obj(n, p);
        if (trace >= 3) print_bounds(m, n, p);
	}
    return count;
}

int n;
double ab[NN][NN], x[NN];

void solve() {
	int p[NN], k = 0;
	for(int i = 0; i < n; i++) p[i] = i;
	for(int col = 0; col < n && k < n; col++) {
		double best = fabs(ab[k][col]);
		int besti = k, bestj = col;
		for(int i = k; i < n; i++)
			for(int j = col; j < n; j++)
				if(fabs(ab[i][j]) > best)
					best = fabs(ab[besti = i][bestj = j]);
		if(best < EPS) continue;
		if(besti != k)
			for(int j = col; j <= n; j++)
				swap(ab[k][j], ab[besti][j]);
		if(bestj != col) {
			for(int i = 0; i < n; i++)
				swap(ab[i][col], ab[i][bestj]);
			swap(p[col], p[bestj]);
		}
		for(int i = k+1; i < n; i++) {
			double mul = -ab[i][col]/ab[k][col];
			for(int j = col; j <= n; j++)
				ab[i][j] += mul * ab[k][j];
		}
		k++;
	}

	for(int i = 0; i < n; i++) x[i] = 0.0;
	for(int i = k-1, j; i >= 0; i--) {
		for(j = 0; j < n && fabs(ab[i][j]) < EPS; j++);
		double sum = ab[i][n];
		for(int k = j+1; k < n; k++)
			sum -= ab[i][k] * x[p[k]];
		x[p[j]] = sum / ab[i][j];
	}
}

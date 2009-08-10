/* LU-DECOMPOSITION (Cormen, p. 749) */
void ludecomp(double a[NN][NN], double l[NN][NN], double u[NN][NN], int n) {
	int i, j, k;
	for(k = 0; k < n; k++) {
		l[k][k] = 1.0;
		u[k][k] = a[k][k];
		for(i = k+1; i < n; i++) {
			l[k][i] = 0.0;
			l[i][k] = a[i][k] / u[k][k];
			u[k][i] = a[k][i];
		}
		for(i = k+1; i < n; i++)
			for(j = k+1; j < n; j++)
				a[i][j] = a[i][j] - l[i][k]*u[k][j];
	}
}

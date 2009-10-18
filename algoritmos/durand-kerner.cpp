int n;			// grau
double a[NN];	// coeficientes
im r[NN];		// raizes

im f(im x) {
	im r, t(1.0);
	for(int i = 0; i <= n; i++, t = t*x) r = r + t*a[i];
	return r;
}

void solve() {
	int i, j, k;
	r[0] = im(1.0);
	for(i = 1; i < n; i++) r[i] = r[i-1]*im(0.4, 0.9);
	for(i = 0; i < ITERS; i++) {
		for(j = 0; j < n; j++) {
			im d = f(r[j]);
			for(k = 0; k < n; k++) if(j != k) d = d/(r[j] - r[k]);
			r[j] = r[j] - d;
		}
	}
}

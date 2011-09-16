#define NN 1024
#define ITERS 500

typedef complex<double> cdouble;

int n;
double a[NN];
cdouble r[NN];

/* f(x) = a[0] + a[1]*x + ... + a[n]*x^n */
cdouble f(cdouble x) {
	im r, t(1.0);
	for(int i = 0; i <= n; i++, t = t*x) r = r + t*a[i];
	return r;
}

void solve() {
	int i, j, k;
	for(i = 0; i <= n; i++) a[i] /= a[n]; // garante a[n] = 1.0
	r[0] = cdouble(1.0, 0.0);
	for(i = 1; i < n; i++) r[i] = r[i-1]*cdouble(0.4, 0.9);
	for(i = 0; i < ITERS; i++) {
		for(j = 0; j < n; j++) {
			cdouble d = f(r[j]);
			for(k = 0; k < n; k++) if(j != k) d = d/(r[j] - r[k]);
			r[j] = r[j] - d;
		}
	}
}

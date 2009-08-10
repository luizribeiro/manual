double det(double a[NN][NN], int n) {
	double l[NN][NN], u[NN][NN], d = 1.0;
	ludecomp(a, l, u, n);
	for(int i = 0; i < n; i++) d *= u[i][i];
	return d;
}

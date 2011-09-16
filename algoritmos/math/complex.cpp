struct im {
	double a, b; /* a + bj */
	im() { a = b = 0.0; }
	im(double x) { a = x, b = 0.0; }
	im(double x, double y) { a = x, b = y; }

	im operator+(double x) const { return im(a+x, b); }
	im operator-(double x) const { return im(a-x, b); }
	im operator*(double x) const { return im(a*x, b*x); }
	im operator/(double x) const { return im(a/x, b/x); }

	im operator+(im x) const { return im(a+x.a, b+x.b); }
	im operator-(im x) const { return im(a-x.a, b-x.b); }
	im operator*(im x) const { return im(a*x.a - b*x.b, a*x.b + b*x.a); }
	im operator/(im x) const { return im(a*x.a + b*x.b, b*x.a - a*x.b)/x.abs2(); }

	double abs2() { return a*a + b*b; }
	bool operator==(im x) const { return fabs(a-x.a) < EPS && fabs(b-x.b) < EPS; }

	bool isReal() { return fabs(b) < EPS; }
};

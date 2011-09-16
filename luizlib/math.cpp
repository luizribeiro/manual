/*
   luizribeiro's topcoder library
   math.cpp
*/

/* Useful Stuff {{{
Largest Prime Numbers
---------------------
For signed 32 bit values:
	2^31-1 = 0x7FFFFFFF = 2,147,483,647

For unsigned 32 bit values:
	2^32-5 = 0xFFFFFFFB = 4,294,967,291
}}} */

/* Sieve of Eratosthenes {{{ */
#define NN 1000000
#define SQRT_NN 1000

#define isPrime(x) prime[x]

bool prime[NN];
void sieve(void) {
	for(int i = 0; i < NN; i++) prime[i] = true;
	prime[0] = prime[1] = false;
	for(int i = 0; i <= SQRT_NN; i++)
		if(prime[i])
			for(int k = i*i; k < NN; k += i)
				prime[k] = false;
}
/* }}} */

/* Prime Factorization {{{ */
#define NN 1000000
#define SQRT_NN 1000

#define isPrime(x) (x > 1 && !prime[x])

int prime[NN];
void sieve(void) {
	for(int i = 0; i <= SQRT_NN; i++)
		if(isPrime(i))
			for(int k = i*i; k < NN; k += i)
				if(!prime[k]) prime[k] = i;
}

int numfactors(int x) {
	// CUIDADO! x > 1
	vector<int> factors;
	int ret = 0;

	while(!isPrime(x)) {
		ret++;
		factors.push_back(prime[x]);
		x /= prime[x];
	}

	if(x > 1) factors.push_back(prime[x]);

	return factors.size();
}
/* }}} */

/* Primality Test O(sqrt(n)) {{{ */
template<class _t> bool isPrime(_t n) {
	if(n < 2) return false;
	for(_t i = 2; i*i <= n; i++)
		if(n % i == 0) return false;
	return true;
}
/* }}} */

/* Bigmod (b^p % m) {{{ */
template<class _T> square(_T x) { return x*x; }
template<class _T> bigmod(_T b, _T p, _T m) { 
	if(p == 0) return 1; 
	else if(p % 2 == 0) return square(bigmod(b, p/2, m)) % m;
	return ((b % m) * bigmod(b, p-1, m)) % m; 
} 
/* }}} */

/* GCD/LCM {{{ */
template<class _T> _T gcd(_T a, _T b) { return a ? gcd(b%a, a) : b; } 
template<class _T> _T lcm(_T a, _T b) { return a * b / gcd(a, b); }
/* }}} */

/* Modular Multiplicative Inverse {{{ */
// Solves ax == b (mod m)
long long axbmodm(long long a, long long b, long long m) {
	return a ? (axbmodm(m%a, (a-b%a)%a, a)*m+b)/a : a;
}

long long invmod(long long a, long long m) {
	return axbmodm(a, 1, m);
}
/* }}} */

/* Modular Binomial Coefficients {{{ */
long long cmod(long long n, long long k, long long m) {
	long long ret = 1;
	for(long long i = n; i > max(n-k, k); i--) ret = (ret*i)%m;
	for(long long i = min(n-k, k); i > 1; i--) ret = (ret*invmod(i, m))%m;
	return ret;
}
/* }}} */

/* Binomial Coefficients {{{ */
long long C[CC][CC];

void calcC(void) {
	for(int i = 0; i < CC; i++) {
		C[i][0] = 1, C[i][i+1] = 0;
		for(int j = 1; j <= i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
}
/* }}} */

/* Complex Numbers {{{ */
#define EPS 1E-9

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
/* }}} */

/* Durand-Kerner {{{ */
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
/* }}} */

/* Gaussian Elimination {{{ */
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
/* }}} */

/* Primitive Pythagorean Triples Generator {{{ */
#define CC 100
void gen(int a = 3, int b = 4, int c = 5) {
	if(c > CC) return;
	printf("%d^2 + %d^2 = %d^2\n", a, b, c);
	gen( a - 2*b + 2*c,  2*a - b + 2*c,  2*a - 2*b + 3*c);
	gen( a + 2*b + 2*c,  2*a + b + 2*c,  2*a + 2*b + 3*c);
	gen(-a + 2*b + 2*c, -2*a + b + 2*c, -2*a + 2*b + 3*c);
}
/* }}} */


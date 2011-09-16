template<class _T> square(_T x) { return x*x; }
template<class _T> bigmod(_T b, _T p, _T m) {
	if(p == 0) return 1;
	else if(p % 2 == 0) return square(bigmod(b, p/2, m)) % m;
	return ((b % m) * bigmod(b, p-1, m)) % m;
}

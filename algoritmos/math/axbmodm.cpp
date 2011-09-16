// Solves ax == b (mod m)
long long axbmodm(long long a, long long b, long long m) {
	return a ? (axbmodm(m%a, (a-b%a)%a, a)*m+b)/a : a;
}

long long invmod(long long a, long long m) {
	return axbmodm(a, 1, m);
}

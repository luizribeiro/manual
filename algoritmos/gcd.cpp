long long gcd(long long a, long long b) { 
	if(a % b == 0) return b;
	return gcd(b, a % b);
} 

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

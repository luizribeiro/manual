#define FOR(i,n)	for(int i = 0; i < n; ++i)
#define BASE		1000
#define DIGITS		1000
#define LOG10BASE	3
struct BigInt {
	int num[DIGITS];
	void clear(){ FOR(i, DIGITS) num[i] = 0; }
	void carry(){
		int c = 0;
		FOR(i, DIGITS){
			c = (num[i] += c) / BASE;
			num[i] %= BASE;
		}
	}
	int get_last(){ int i; for(i = DIGITS; i-- && !num[i]; ); return i + 1; }
	void show(){
		int i = get_last(), j, k;
		char c[LOG10BASE + 1];
		c[LOG10BASE] = 0;
		printf("%d", num[--i]);
		while(i--){
			for(j = LOG10BASE, k = num[i]; j--; c[j] = k%10 + '0', k /= 10);
			printf("%s", c);
		}
		puts("");
	}
	BigInt(int v = 0){ clear(); num[0] = v; carry(); }
	BigInt(char *v){
		char *last = v;
		int mult, pos = 0, z;
		clear();
		while(*last) ++last; --last;
		while(last >= v){
			mult = 1; z = 0;
			FOR(i, LOG10BASE){
				z = mult * (*last - '0') + z;
				mult *= 10;
				if(--last < v) break;
			}
			num[pos++] = z;
		}
	}
	BigInt(string v){ BigInt(v.c_str()); }
	BigInt(BigInt* b){ FOR(i, DIGITS) num[i] = b->num[i]; }
	BigInt operator+(BigInt b){
		BigInt r = this;
		FOR(i, DIGITS) r.num[i] += b.num[i];
		r.carry();
		return r;
	}
	BigInt operator*(BigInt b){
		BigInt r;
		int lim_i = get_last(), lim_j = b.get_last();
		FOR(i, lim_i) FOR(j, lim_j) r.num[i+j] += num[i] * b.num[j];
		r.carry();
		return r;
	}
	BigInt operator+=(BigInt b){ return *this = *this + b; }
	BigInt operator*=(BigInt b){ return *this = *this * b; }
	int compare(const BigInt b){
		int lim_i = get_last(), lim_j = get_last();
		if(lim_i != lim_j) return (lim_i > lim_j) - (lim_i < lim_j);
		for(int x = lim_i; x--; )
			if(num[x] != b.num[x]) return (num[x] > b.num[x]) - (num[x] < b.num[x]);
		return 0;
	}
	bool operator>(BigInt b){ return compare(b) == 1; }
	bool operator>=(BigInt b){ return compare(b) > -1; }
	bool operator==(BigInt b){ return compare(b) == 0; }
	bool operator<(BigInt b){ return compare(b) == -1; }
	bool operator<=(BigInt b){ return compare(b) < 1; }
	bool operator!=(BigInt b){ return compare(b) != 0; }
};

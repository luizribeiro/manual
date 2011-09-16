/*
   luizribeiro's topcoder library
   dp.cpp
*/

/* Longest Increasing Subsequence {{{ */
vector<int> a;
bool liscmp(int i, int j) { return a[i] < a[j]; }
vector<int> lis() {
	int n = a.size();
	int x[n], p[n], L; // indices, predecessores, tamanho
	vector<int> ans;

	L = 0;
	x[L++] = 0;
	memset(p, -1, sizeof(p));
	for(int i = 1; i < n; i++) {
		int j = lower_bound(x, x+L, i, liscmp) - x; // upper_bound para non-decreasing
		if(j == L) {
			p[i] = x[L-1];
			x[L++] = i;
		} else if(a[i] < a[x[j]]) {
			if(j) p[i] = x[j-1];
			x[j] = i;
		}
	}

	for(int u = x[L-1], v = L; v--; u = p[u]) x[v] = u; // arruma indices
	for(int i = 0; i < L; i++) ans.push_back(a[x[i]]);

	return ans;
}
/* }}} */

/* Damerau-Levenshtein Edit Distance {{{ */
int damlevdist(char *a, char *b) {
	const int CI = 1, CR = 1, CD = 1, CS = 1; // 2*CS >= CI + CD
	int n = strlen(a), m = strlen(b);
	int dp[n+1][m+1];
	int la[26], lb;
	for(int i = 0; i <= n; i++) dp[i][0] = i;
	for(int j = 0; j <= m; j++) dp[0][j] = j;
	for(int i = 0; i < 26; i++) la[i] = 0; // ultima ocorrencia do caracter i na string a
	for(int i = 1; i <= n; i++) {
		lb = 0; // ultima ocorrencia de a[i-1] na string b
		for(int j = 1; j <= m; j++) {
			dp[i][j] = a[i-1] == b[j-1] ? dp[i-1][j-1] : 0x3f3f3f3f;
			dp[i][j] = min(dp[i][j], dp[i-1][j-1] + CR); // replace
			dp[i][j] = min(dp[i][j], dp[i][j-1] + CI); // insertion
			dp[i][j] = min(dp[i][j], dp[i-1][j] + CD); // deletion

			// swap
			int ii = la[b[j-1]-'a'], jj = lb;
			if(ii && jj) dp[i][j] = min(dp[i][j], dp[ii-1][jj-1] + (i-ii-1)*CD + (j-jj-1)*CI + CS);
			if(a[i-1] == b[j-1]) lb = j;
		}
		la[a[i-1]-'a'] = i;
	}
	return dp[n][m];
}
/* }}} */

/* Range Minimum Query {{{ */
int a[NN], n; // valores, numero de valores
int m[NN][LOGNN]; // m[i][j] = indice com o menor valor no intervalo [i, i+2^j[

void precalc(void) {
	for(int i = 0; i < n; i++)
		m[i][0] = i;

	for(int j = 1; 1 << j <= n; j++)
		for(int i = 0; i + (1 << j) - 1 < n; i++)
			if(a[m[i][j-1]] < a[m[i + (1 << (j-1))][j-1]])
				m[i][j] = m[i][j-1];
			else
				m[i][j] = m[i + (1 << (j-1))][j-1];
}

int rmq(int i, int j) {
	int k, x = j - i + 1;
	for(k = 0; x >>= 1; k++);
	return a[m[i][k]] <= a[m[j - (1 << k) + 1][k]] ? m[i][k] : m[j - (1 << k) + 1][k];
}
/* }}} */


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

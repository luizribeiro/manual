char text[TT], patt[PP]; // text, pattern
int n, m; // strlen(text), strlen(pattern)
int f[PP]; // failure table

void buildf(void) {
	f[0] = f[1] = 0;
	for(int i = 2; i <= m; i++) {
		f[i] = -1;
		for(int j = f[i-1]; f[i] == -1; j = f[j])
			if(patt[j] == patt[i-1]) f[i] = j+1;
			else if(j == 0) f[i] = 0;
	}
}

void kmp(void) {
	buildf();
	for(int i = 0, j = 0; j < n; j++) {
		// i = automaton's state, j = text position
		if(text[j] == patt[i]) {
			i++; // move to next state
			if(i == m) {
				printf("found match at index %d\n", j-m+1);
				i = f[i];
			}
		} else if(i) i = f[i], j--;
	}
}

/* KMP's properties {{{

if(f[i] > 0 && (i % (i - f[i])) == 0)
	prefix with size i is periodic, with period length = (i - f[i])

}}} */

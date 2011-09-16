char text[TT][TT], patt[PP][PP]; // text, pattern [row][col]
int n1, n2; // num of rows, cols patt
int m1, m2; // num of rows, cols text
int f[PP]; // failure table

void buildf(void) {
	f[0] = f[1] = 0;
	for(int i = 2; i <= n1; i++) {
		f[i] = -1;
		for(int j = f[i-1]; f[i] == -1; j = f[j])
			if(strcmp(patt[j], patt[i-1]) == 0) f[i] = j+1;
			else if(j == 0) f[i] = 0;
	}
}

void kmp(void) {
	buildf();
	for(int k = 0; k <= m2-n2; k++) {
		for(int i = 0, j = 0; j < m1; j++) {
			// i = automaton's state, j = text position
			if(strncmp(text[j]+k, patt[i], n2) == 0) {
				i++;
				if(i == n1) {
					printf("found match at (%d, %d)\n", j-n1+2, k+1);
					i = f[i];
				}
			} else if(i) i = f[i], j--;
		}
	}
}

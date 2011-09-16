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

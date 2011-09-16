// P deve ser inicializado com -1
int P[NN][LOGNN], L[NN]; // P[i][j] pai de i 2^j niveis acima, L[i] nivel de i
int N; // Numero de nos
void compute_lca(){ // Pre-computacao em O(NlogN)
	for(int j = 1; (1 << j) < N; ++j)
		for(int i = 0; i < N; ++i)
			if(P[i][j - 1] != -1)
				P[i][j] = P[P[i][j - 1]][j - 1];
}
// Consulta, retorna o LCA de p e q
int query(int p, int q) { // Consulta em O(logN)
	int log, i;
	if (L[p] < L[q]) p ^= q ^= p ^= q;
	for (log = 1; 1 << log <= L[p]; log++);
	log--;
	for (i = log; i >= 0; i--)
		if (L[p] - (1 << i) >= L[q])
			p = P[p][i];
	if (p == q) return p;
	for (i = log; i >= 0; i--)
		if (P[p][i] != -1 && P[p][i] != P[q][i])
			p = P[p][i], q = P[q][i];
	return P[p][0];
}


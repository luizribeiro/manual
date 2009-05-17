int eu[MM], ev[MM]; /* lista de arestas (u,v) (eu[i], ev[i]) */
int d[NN][NN]; /* matriz de adjacencia */

int bellmanford(int s, int t) {
	int di[N], p[N];
	int i, j;

	for(i = 0; i < n; i++)
		di[i] = INF, p[i] = -1;

	di[s] = 0;

	for(j = 0; j < n; j++) {
		bool trocou = false;
		for(i = 0; i < m; i++) {
			int u = eu[i], v = ev[i];
			if(di[v] > di[u] + d[u][v]) {
				di[v] = di[u] + d[u][v];
				p[v] = u;
				trocou = true;
			}
		}
		if(!trocou) break;
	}

	return di[t];
}

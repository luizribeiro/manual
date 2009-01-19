/* TODO: tornar decente */
long long bellmanford(int s, int t) {
	long long di[N];
	int i, j;

	for(i = 0; i < n; i++) {
		di[i] = INF;
		p[i] = -1;
	}

	di[s] = 0;

	for(j = 0; j < n; j++) {
		bool trocou = false;
		for(i = 0; i < m; i++) {
			int u = eu[i];
			int v = ev[i];
			if(cap - f[u][v] > 0 && di[v] > di[u] + d[u][v]) {
				di[v] = di[u] + d[u][v];
				p[v] = u;
				trocou = true;
			}
			if(cap - f[v][u] > 0 && di[u] > di[v] + d[v][u]) {
				di[u] = di[v] + d[v][u];
				p[u] = v;
				trocou = true;
			}
		}
		if(!trocou) break;
	}

	return di[t];
}

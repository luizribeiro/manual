int n;
vector<int> adj[NN];
int num[NN], low[NN], scc[NN];
int cnt, scccnt;
stack<int> s;

void dfs(int u) {
	num[u] = low[u] = cnt++;
	s.push(u);
	for(int i = 0; i < (int)adj[u].size(); i++) {
		int v = adj[u][i];
		if(num[v] == -1) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(scc[v] == -1) {
			low[u] = min(low[u], num[v]);
		}
	}

	if(low[u] == num[u]) {
		for(int v = -1; v != u; s.pop()) scc[v = s.top()] = scccnt;
		scccnt++;
	}
}

void findscc(void) {
	for(int i = 0; i < n; i++) num[i] = scc[i] = -1;
	scccnt = 0;
	for(int i = 0; i < n; i++)
		if(num[i] == -1) cnt = 0, dfs(i);
}

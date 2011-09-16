vector<int> adj[NN];
int used[NN], pairs[NN], n; // i pairs with pairs[i]

bool dfs(int u) {
	if(used[u]) return false;
	used[u] = true;
	for(int i = 0; i < (int)adj[u].size(); i++) {
		int v = adj[u][i];
		if(pairs[v] == -1 || dfs(pairs[v])) {
			pairs[v] = u;
			return true;
		}
	}
	return false;
}

int bpm() {
	int numpairs = 0;
	for(int i = 0; i < n; i++) pairs[i] = -1;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) used[j] = 0;
		dfs(i);
	}
	for(int i = 0; i < n; i++)
		numpairs += pairs[i] != -1;
	return numpairs/2;
}

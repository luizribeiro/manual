int n;
vector<int> adj[NN], jda[NN]; /* G, G^T */
int vis[NN], num[NN], scc[NN];
int cnt, scccnt;

void dfs(int v) {
	int i;
	vis[v] = 1;
	for(i = 0; i < (int)adj[v].size(); i++)
		if(!vis[adj[v][i]]) dfs(adj[v][i]);
	num[cnt++] = v;
}

void dfst(int v) {
	int i;
	vis[v] = 1;
	scc[v] = scccnt;
	for(i = 0; i < (int)jda[v].size(); i++)
		if(!vis[jda[v][i]]) dfst(jda[v][i]);
}

void findscc() {
	int i;
	/* dfs em G */
	for(i = 0; i < n; i++) vis[i] = 0;
	cnt = 0;
	for(i = 0; i < n; i++)
		if(!vis[i]) dfs(i);

	/* dfs em G^T */
	for(i = 0; i < n; i++) vis[i] = 0;
	scccnt = 0;
	for(i = n-1; i >= 0; i--)
		if(!vis[num[i]]) dfst(num[i]), scccnt++;
}

int n;
vector<int> adj[NN];
stack< pair<int, int> > s;									// BCC
int num[NN], low[NN];
int cnt;

void dfs(int u, int prnt = -1) {
	low[u] = num[u] = cnt++;

	for(int i = 0; i < (int)adj[u].size(); i++) {
		int v = adj[u][i];
		if(num[v] == -1) {
			s.push(make_pair(u, v));						// BCC
			dfs(v, u);
			low[u] = min(low[u], low[v]);

			if((num[u] != 0 && low[v] >= num[u]) || (num[u] == 0 && num[v] != 1)) {
				/* u eh pto de articulacao */
				printf("found cut vertex: %d\n", u);
			}

			/* Biconnected Components */
			if(low[v] >= num[u]) {
				printf("found biconnected component: ");
				for(pair<int,int> p; p != make_pair(u,v); s.pop()) {
					p = s.top();
					printf("%d-%d ", p.first, p.second);
				}
				printf("\n");
			}

			if(low[v] == num[v]) {
				/* u-v eh ponte */
				printf("found bridge: %d-%d\n", u, v);
			}
		} else if(v != prnt) {
			if(num[v] < num[u]) s.push(make_pair(u, v));	// BCC
			low[u] = min(low[u], num[v]);
		}
	}
}

void findcuts(void) {
	memset(num, -1, sizeof(num));
	for(int i = 0; i < n; i++)
		if(num[i] == -1) cnt = 0, dfs(i);
}

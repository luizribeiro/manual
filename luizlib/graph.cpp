/*
   luizribeiro's topcoder library
   graph.cpp
*/

/* Dijkstra {{{ */
const int INF = 0x3f3f3f3f;

int nno, ned;
struct edge {
	int u, v, cost, next;
	edge(int _u, int _v, int _cost, int _next = -1) :
		u(_u), v(_v), cost(_cost), next(_next) {}
};
vector<edge> edges;
vector<int> first;

int dijkstra(int s, int t) {
	priority_queue< pair<int,int> > q;
	vector<int> d(nno, INF), in(nno, 0);
	d[s] = 0;
	q.push(make_pair(-d[s], s));
	while(!q.empty() && !in[t]) {
		s = q.top().second; q.pop();
		if(in[s]) continue;
		in[s] = 1;
		for(int i = first[s]; i != -1; i = edges[i].next) {
			if(!in[edges[i].v] && d[edges[i].v] > d[s] + edges[i].cost) {
				d[edges[i].v] = d[s] + edges[i].cost;
				q.push(make_pair(-d[edges[i].v], edges[i].v));
			}
		}
	}
	return d[t];
}

void reset(int n) {
	nno = n, ned = 0, edges.clear();
	first = vector<int>(nno, -1);
}

void addedge(int u, int v, int cost) {
	edges.push_back(edge(u, v, cost, first[u])); first[u] = ned++;
}
/* }}} */

/* Bellman-Ford {{{ */
struct { int u, v, w; } e[MM]; /* arestas (u,v) com peso w */

int bellmanford(int s, int t) {
	int di[NN], p[NN]; /* distancias e predecessores */
	int i, j;

	for(i = 0; i < n; i++)
		di[i] = INF, p[i] = -1;

	di[s] = 0;

	for(j = 0; j < n; j++) {
		bool trocou = false;
		for(i = 0; i < m; i++) {
			int u = e[i].u, v = e[i].v;
			if(di[v] > di[u] + e[i].w) {
				di[v] = di[u] + e[i].w;
				p[v] = u;
				trocou = true;
			}
		}
		if(!trocou) break;
	}

	return di[t];
}
/* }}} */

/* Edmonds-Karp {{{ */
const int INF = 0x3f3f3f3f;

int nno, ned;
struct edge {
	int u, v, cap, flow, next;
	edge(int _u, int _v, int _cap, int _next = -1) :
		u(_u), v(_v), cap(_cap), next(_next) { flow = 0; }
};
vector<edge> edges;
vector<int> first, prev;

bool bfs(int s, int t) {
	vector<int> vis(nno, 0);
	queue<int> q;
	prev = vector<int>(nno, -1);
	q.push(s), vis[s] = 1;
	while(!q.empty() && !vis[t]) {
		s = q.front(); q.pop();
		for(int i = first[s]; i != -1; i = edges[i].next) {
			if(!vis[edges[i].v] && edges[i].cap - edges[i].flow > 0) {
				q.push(edges[i].v), vis[edges[i].v] = 1;
				prev[edges[i].v] = i;
			}
		}
	}
	return vis[t];
}

int maxflow(int s, int t) {
	int mf = 0;
	while(bfs(s, t)) {
		int cf = INF;
		for(int i = prev[t]; i != -1; i = prev[edges[i].u])
			cf = min(cf, edges[i].cap - edges[i].flow);
		for(int i = prev[t]; i != -1; i = prev[edges[i].u])
			edges[i].flow += cf, edges[i^1].flow -= cf;
		mf += cf;
	}
	return mf;
}

void reset(int n) {
	nno = n, ned = 0, edges.clear();
	first = vector<int>(nno, -1);
}

void addedge(int u, int v, int cap) {
	edges.push_back(edge(u, v, cap, first[u])); first[u] = ned++;
	edges.push_back(edge(v, u,   0, first[v])); first[v] = ned++;
}
/* }}} */

/* Min-Cost Max-Flow {{{ */
const int INF = 0x3f3f3f3f;

int nno, ned;
struct edge {
	int u, v, cost, cap, flow, next;
	edge(int _u, int _v, int _cost, int _cap, int _next = -1) :
		u(_u), v(_v), cost(_cost), cap(_cap), next(_next) { flow = 0; }
};
vector<edge> edges;
vector<int> first, prev;

int bellmanford(int s, int t) {
	vector<int> d(nno, INF);
	prev = vector<int>(nno, -1);
	d[s] = 0;
	for(int k = 0; k < nno; k++) {
		bool ok = true;
		for(int i = 0; i < ned; i++) {
			int u = edges[i].u, v = edges[i].v;
			if(edges[i].cap - edges[i].flow > 0 && d[v] > d[u] + edges[i].cost) {
				prev[v] = i;
				d[v] = d[u] + edges[i].cost;
				ok = false;
			}
		}
		if(ok) break;
	}
	return d[t];
}

void mincostmaxflow(int &fcost, int &flow, int s, int t) {
	fcost = flow = 0;
	while(bellmanford(s, t) < INF) {
		int cf = INF;
		for(int i = prev[t]; i != -1; i = prev[edges[i].u])
			cf = min(cf, edges[i].cap - edges[i].flow);
		for(int i = prev[t]; i != -1; i = prev[edges[i].u]) {
			edges[i].flow += cf, edges[i^1].flow -= cf;
			fcost += cf * edges[i].cost;
		}
		flow += cf;
	}
}

void reset(int n) {
	nno = n, ned = 0, edges.clear();
	first = vector<int>(nno, -1);
}

void addedge(int u, int v, int cost, int cap) {
	edges.push_back(edge(u, v,  cost, cap, first[u])); first[u] = ned++;
	edges.push_back(edge(v, u, -cost,   0, first[v])); first[v] = ned++;
}
/* }}} */

/* Kuhn's Algorithm (BPM) {{{ */
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
/* }}} */

/* Cut Vertices and Bridges and Biconnected Components {{{ */
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
/* }}} */

/* Tarjan SCC {{{ */
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
/* }}} */

/* Kosaraju SCC {{{ */
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
/* }}} */


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

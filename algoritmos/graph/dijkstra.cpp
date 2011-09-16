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

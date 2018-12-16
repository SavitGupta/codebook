/*
Kruskal MST
Initialisation:
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		graph.pb(edge(x, y, w));
	}
	Kruskal(n);
About : spanning_tree will store edges
		mincost will store MST weight
*/

struct edge {
	int u, v, w;
	edge(int u, int v, int w): u(u), v(v), w(w) {}
};

// struct cmp {
// 	bool operator()(const edge& a, const edge& b) const {
// 		return a.w < b.w;
// 	}
// }
// set<edge, cmp> s;
// priority_queue<edge, vector<edge>, cmp> q;

const int N = 1e5 + 10;
vector<edge> graph, spanning_tree;
int mincost = 0;
int dsu[N], sz[N];

bool edge_sort(const edge &a, const edge &b) {
	return a.w < b.w;
}

int findparent(int u) {
	if(dsu[u] == u) return u;
	return dsu[u] = findparent(dsu[u]);
}

void merge(edge e) {
	int u = e.u;
	int v = e.v;
	if(u == v) return; //self loops
	if(sz[v] > sz[u]) {
		swap(u, v);
	}
	dsu[v] = u;
	sz[u] += sz[v];
}

void Kruskal(int n) {
	//1-based
	sort(all(graph), edge_sort);
	for(int i = 1; i <= n; i++) {
		dsu[i] = i;
		sz[i] = 1;
	}
	for(edge e : graph) {
		int x = findparent(e.u);
		int y = findparent(e.v);
		if(x == y) continue;
		spanning_tree.pb(e);
		mincost += e.w;
		merge(e);
	}
}

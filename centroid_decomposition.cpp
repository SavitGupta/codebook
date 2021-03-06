// Decomposed Tree's root is decom[0].
// 1-based tree only
// Add both side edges

const int N = 1e5 + 10;
int n;
int sz[N];
set <int> graph[N];
vector<int> decom[N];

int get_size(int u, int par) {                           // Get sizes of subtrees
    sz[u] = 1;
    for(int v: graph[u]) {
        if(v != par)
            sz[u] += get_size(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int par, int total) {
    for(int v: graph[u]) {
        if(v == par) continue;
        if(2 * sz[v] > total) return get_centroid(v, u, total);
    }
    return u;
}

void decompose(int u, int par = 0) {
    int total = get_size(u, -1);                            // Size of component to be decomposed
    int centroid = get_centroid(u, -1, total);              // Get centroid of current tree
    decom[par].pb(centroid);                                // Making decomposed tree

    for(int v: graph[centroid]) {
        graph[v].erase(centroid);
        decompose(v, centroid);                             // Decompose subtrees
    }
}

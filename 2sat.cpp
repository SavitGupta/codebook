/*
    2-SAT Template
    Given an implication graph, this checks if a solution exists.

    addXor(), addAnd(), addOr() can be used to appropriately add clauses.
    forceTrue() forces some variable to be true.
    forceFalse() forces some variable to be false.

    You can also add additional implications yourself.
    init() initializes 2-SAT arrays.
    solve() checks if in the final implication graph, a valid solution exists.
    mark[u] stores the boolean value of the node (u). You can use mark[] to
    recover the final solution as well.

    Notes on Indexing Nodes :
    u = 2k, !u = 2k + 1
    Nodes are 0-indexed. [0, NUM_VERTICES)
*/

const int N = (int) 5e5 + 10;
int n;                          // Number of Nodes(excluding negation)
int NUM_VERTICES, id;
int arr[N * 2];
vector < int > adj[N * 2];
bool mark[N * 2];

inline bool dfs(int node) {
    if (mark[node ^ 1]) {
        return false;
    }
    if (mark[node]) {
        return true;
    }
    mark[node] = true;
    arr[id++] = node;
    for (int i = 0; i < (int) adj[node].size(); i++) {
        if (!dfs(adj[node][i])) {
            return false;
        }
    }
    return true;
}

inline void init() {
    NUM_VERTICES = 2 * n;
    for (int i = 0; i < NUM_VERTICES; i++) {
        adj[i].clear();
    }
    memset(mark, 0, sizeof(mark));
}

// Adds the clause (u or v) to the set of clauses
inline void addOr(int u, int v) {
    adj[u ^ 1].push_back(v);
    adj[v ^ 1].push_back(u);
}

// Adds the clause (u == v) to the set of clauses
inline void addEquivalent(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    adj[u ^ 1].push_back(v ^ 1);
    adj[v ^ 1].push_back(u ^ 1);
}

// Adds the clause (u xor v) to the set of clauses
inline void addXor(int u, int v) {
    addOr(u, v);
    addOr(u ^ 1, v ^ 1);
}

// Forces variable (u) to be true
inline void forceTrue(int u) {
    adj[u ^ 1].push_back(u);
}

// Forces variable (u) to be false
inline void forceFalse(int u) {
    adj[u].push_back(u ^ 1);
}

// Adds the clause (u and v) to the set of clauses
inline void addAnd(int u, int v) {
    forceTrue(u);
    forceTrue(v);
}

inline void addImplication(int u, int v) {
	adj[u].push_back(v);
}

// Returns true if a solution exists.
inline bool solve() {
    for (int i = 0; i < NUM_VERTICES; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());
    }
    for (int i = 0; i < NUM_VERTICES; i += 2) {
        if ((!mark[i]) && (!mark[i + 1])) {
            id = 0;
            if(!dfs(i)) {
                while (id > 0) {
                    mark[arr[--id]] = false;
                }
                if(!dfs(i + 1)) {
                    return false;
                }
            }
        }
    }
    return true;
}

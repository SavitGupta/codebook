
const int N = 1e5 + 10;
vector<int> adj[N];
bool visited[N] = {0};
vector<pll> bridges;
vector<int> cutPts;

// Use p = -1 for root
void dfs(int u, int p = -1, int d = 0){
    visited[u] = true;
    dep[u] = d;
    fup[u] = d;
    bool isCutpt = false;
    for(int v : adj[u]){
        if(v == p)
            continue;
        if(not visited[v]){
            dfs(v, u, d+1);
            fup[u] = min( fup[u] , fup[v] );
            //Cut-Vertices
            if(fup[v] >= dep[u]){
                if(p != -1){ //Excluding root
                    isCutpt = true;
                }
                else if(adj[u].size() > 1){ //For root
                    isCutpt = true;
                }
            }
            //Bridges
            if(fup[v] > dep[u]){
                bridges.pb(mp(u,v));
            }

        }
        else{
            fup[u] = min(fup[u], dep[v]);
        }    
    }
    //Cut - Vertices
    if(isCutpt){
        cutPts.pb(u);
    }
}

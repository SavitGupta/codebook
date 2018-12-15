const int N = 1e5+10;
vector<pair<int, int>> adj[N];
bool vis[N] = {0};
void dijkstra(int v, int d[], int n)
{
	fill(d, d+n, 1e18+10);
	d[v] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	pq.push({d[v], v});
	while(!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		if(vis[u])
		{
			continue;
		}
		vis[u] = true;
		for(auto it : adj[u])
		{
			if(d[it.first] > d[u] + it.second)
			{
				d[it.first] = d[u] + it.second;
				pq.push({d[it.first], it.first});
			}
		}
	}
}

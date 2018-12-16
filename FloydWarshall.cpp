void floydwarshall(int n) {
	for(int i = 0; i < n; i++) 
		for(int j = 0; j < n; j++)
			distmat[i][j] = graph[i][j];
		
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				distmat[i][j] = min(distmat[i][j], distmat[i][k] + distmat[k][j]);
}

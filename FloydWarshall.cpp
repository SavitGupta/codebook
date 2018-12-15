void floydwarshall(int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			distmat[i][j] = graph[i][j];
		}
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				if(distmat[j][i] + distmat[i][k] < distmat[j][k])
				{
					distmat[j][k] = distmat[j][i] + distmat[i][k];
				}
			}
		}
	}
}

const int N = 1e6;

int tree[4*N] = {0}; // initialised zero element for rmq
int lazy[4*N] = {0};


int maxquery(int beg, int fin, int qbeg, int qfin, int cur)
{
	if(lazy[cur] != 0)
	{
		tree[cur] = tree[cur] + lazy[cur];
		//doing this because this node represents sum of nodes below it, so total update is value of lazy node multiplied by no. of elements in that nodes subtree
		if(beg != fin)
		{
			lazy[2*cur+1] += lazy[cur];
			lazy[2*cur+2] += lazy[cur];
		}
		lazy[cur] = 0;
	}
	if(beg > fin || beg > qfin || fin < qbeg)
	{
		//no overlap;
		return -1*inf; // ZERO ELEMENT
	}
	if(beg>=qbeg && fin <=qfin)
	{
		//total overlap
		return tree[cur];
	}
	//remaining condition for partial overlap
	int mid = (beg+fin)/2;
	return (max(maxquery(beg, mid, qbeg, qfin, 2*cur+1),maxquery(mid+1, fin, qbeg, qfin,2*cur+2)));
}

void rangeupdate(int cur, int beg, int fin, int ubeg, int ufin, int val)
{
	if(lazy[cur] != 0)
	{
		tree[cur] = tree[cur] + (fin-beg+1)*lazy[cur];
		//doing this because this node represents sum of nodes below it, so total update is value of lazy node multiplied by no. of elements in that nodes subtree
		if(beg !=fin)
		{
			lazy[2*cur+1] += lazy[cur];
			lazy[2*cur+2] += lazy[cur];
		}
		lazy[cur] = 0;
	}
	if(beg > fin || beg > ufin || fin < ubeg)
	{
		//no overlap;
		return;
	}
	if(beg>=ubeg && fin<=ufin)
	{
		tree[cur] += val;

		if(beg != fin)
		{
			lazy[2*cur+1] += val; // updating nodes for rmq
			lazy[2*cur+2] += val; // updating nodes for rmq
		}
		return;
	}
	int mid = (beg+fin)/2;
	rangeupdate(2*cur+1, beg, mid, ubeg, ufin, val);
	rangeupdate(2*cur+2, mid+1, fin, ubeg, ufin, val);
	if(tree[2*cur+1] > tree[2*cur+2])
	{
		tree[cur] = tree[2*cur+1];
	}
	else
	{
		tree[cur] = tree[2*cur+2];
	}
}

void constructtree(int a[], int beg, int fin, int cur)
{
	if(beg > fin)
	{
		return;
	}
	if(beg == fin)
	{
		tree[cur] = a[beg];
		return;
	}
	int mid = (beg+fin)/2;
	constructtree(a, beg, mid, 2*cur+1);
	constructtree(a, mid+1, fin, 2*cur+2);
	if(tree[2*cur+1] > tree[2*cur+2])
	{
		tree[cur] = tree[2*cur+1];
	}
	else
	{
		tree[cur] = tree[2*cur+2];
	}
}

void rangeupdater(int n, int rbeg, int rfin, int val)
{
	rangeupdate(0, 0, n-1, rbeg, rfin, val);
}

int maxquerycaller(int n, int rbeg, int rfin)
{
	return maxquery(0, n-1, rbeg, rfin, 0);
}

const int N = 1e6;
int tree[4*N] = {0}; // initialised zero element for rmq
int lazy[4*N] = {0};

int maxquery(int beg, int fin, int qbeg, int qfin, int cur) {
	if(lazy[cur] != 0) {
		tree[cur] = tree[cur] + lazy[cur];
		//doing this because this node represents sum of nodes below it, so total update is value of lazy node multiplied by no. of elements in that nodes subtree
		if(beg != fin) {
			lazy[2*cur+1] += lazy[cur];
			lazy[2*cur+2] += lazy[cur];
		}
		lazy[cur] = 0;
	}
	if(beg > fin || beg > qfin || fin < qbeg) return -1*inf; // ZERO ELEMENT
	if(beg>=qbeg && fin <=qfin) {
		// For merge sort tree
		// return upper_bound(all(segtree[node]), k) - segtree[node].begin();          // Number of elements <= k in [l, r]
		// return segtree[node].end() - lower_bound(all(segtree[node]), k);         // Number of elements >= k in [l, r]
		// Replace lower and upper to remove equality sign
		return tree[cur];
	}
	int mid = (beg+fin)/2;
	return (max(maxquery(beg, mid, qbeg, qfin, 2*cur+1),maxquery(mid+1, fin, qbeg, qfin,2*cur+2)));
}

void rangeupdate(int cur, int beg, int fin, int ubeg, int ufin, int val) {
	if(lazy[cur] != 0) {
		tree[cur] = tree[cur] + (fin-beg+1)*lazy[cur];
		//doing this because this node represents sum of nodes below it, so total update is value of lazy node multiplied by no. of elements in that nodes subtree
		if(beg !=fin) {
			lazy[2*cur+1] += lazy[cur];
			lazy[2*cur+2] += lazy[cur];
		}
		lazy[cur] = 0;
	}
	if(beg > fin || beg > ufin || fin < ubeg) return;
	
	if(beg>=ubeg && fin<=ufin) {
		tree[cur] += val;
		if(beg != fin) {
			lazy[2*cur+1] += val; // updating nodes for rmq
			lazy[2*cur+2] += val; // updating nodes for rmq
		}
		return;
	}
	int mid = (beg+fin)/2;
	rangeupdate(2*cur+1, beg, mid, ubeg, ufin, val);
	rangeupdate(2*cur+2, mid+1, fin, ubeg, ufin, val);
	tree[cur] = max(tree[2*curr+1], tree[2*curr+2]);
}

void constructtree(int a[], int beg, int fin, int cur)
{
	if(beg > fin) return;
	if(beg == fin) {
		tree[cur] = a[beg];
		return;
	}
	int mid = (beg+fin)/2;
	constructtree(a, beg, mid, 2*cur+1);
	constructtree(a, mid+1, fin, 2*cur+2);
	tree[cur] = max(tree[2*curr+1], tree[2*curr+2]);
// 	    merge(all(segtree[lc]), all(segtree[rc]), back_inserter(segtree[node])) for merge sort tree
	
}

void rangeupdater(int n, int rbeg, int rfin, int val) {
	rangeupdate(0, 0, n-1, rbeg, rfin, val);
}

int maxquerycaller(int n, int rbeg, int rfin) {
	return maxquery(0, n-1, rbeg, rfin, 0);
}

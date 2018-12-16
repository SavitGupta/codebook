const int N = 1e5 + 10;
const int K = 25;               // log2(N)

int table[N][K+1];
int a[N];                       // 0 based
int n;
void build() {
    for(int i = 0; i < n; i++)
		table[i][0] = a[i];

    for(int j = 1; j <= K; j++) {
        for(int i = 0; i + (1 << j) - 1 < n; i++)
            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }
}

int query(int l, int r) {		// RMQ, GCD 
    int j = log2(r - l + 1);
    return min(table[l][j], table[r - (1 << j) + 1][j]);
}

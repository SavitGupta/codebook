const int N = 1e5 + 10;
int z[N];
int b[N];
void zfunction(string s)
{
	int l = 0, r = 0;
	int n = s.size();
	z[0] = 0;
	for(int i = 1; i < n; i++)
	{
		if(r >= i)
		{
			z[i] = min(z[i-l], r - i + 1);
		}
		while(z[i] + i < n && s[z[i]] == s[z[i] + i])
		{
			z[i]++;
		}
		if(z[i] + i - 1 > r)
		{
			l = i;
			r = z[i] + i - 1;
		}
	}
}

void prefixfunction(string s)
{
	b[0] = 0;
	for(int i = 1; i < n; i++)
	{
		int k = b[i-1];
		while(k > 0 && s[k] != s[i])
		{
			k = b[k-1];
		}
		if(s[k] == s[i])
		{
			b[i] = k + 1;
		}
	}
}

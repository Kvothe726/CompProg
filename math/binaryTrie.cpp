const int nmax = (1e5+5)*(31);

struct trie
{
	int psz, cnt[nmax], len[nmax];
	int to[nmax][2];

	trie() { psz = 1; memset(to,-1,sizeof(to));}

	void clear() { for(int i = 0; i < psz; i++) cnt[i] = 0, len[i] = 0; psz = 1; memset(to,-1,sizeof(to));}

	void add(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(to[u][c-'0']==-1) len[psz] = len[u] + 1, to[u][c-'0'] = psz++;
			u = to[u][c-'0']; cnt[u]++;
		}
	}

	void del(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(!to[u][c-'0']==-1) return;
			u = to[u][c-'0']; cnt[u]--;
		}
	}

	int count(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(to[u][c-'0']==-1) return 0;
			u = to[u][c-'0'];
		}

		return cnt[u];
	}
};

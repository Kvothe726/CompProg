const int nmax = (1 << 20); // accomodate the size of string also  = totalstrings*(size+1).

struct trie
{
	int psz, cnt[nmax], len[nmax];
	map<char, int> to[nmax];

	trie() { psz = 1; }

	void clear() { for(int i = 0; i < psz; i++) cnt[i] = 0, len[i] = 0, to[i].clear(); psz = 1; }

	void add(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(!to[u].count(c)) len[psz] = len[u] + 1, to[u][c] = psz++;
			u = to[u][c]; cnt[u]++;
		}
	}

	void del(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(!to[u].count(c)) return;
			u = to[u][c]; cnt[u]--;
		}
	}

	int count(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(!to[u].count(c)) return 0;
			u = to[u][c];
		}

		return cnt[u];
	}
};

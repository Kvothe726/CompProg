// send in total length of strings for constructor not count of strings.
struct trie
{
	int psz;
	vector<int> cnt,len;
	vector<map<char, int>> to;

	trie(int tlen) { // we need to initiate with sum of lengths of strings
		cnt.resize(tlen+5,0);
		len.resize(tlen+5,0);
		to.resize(tlen+5);
		psz = 1;
	}

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

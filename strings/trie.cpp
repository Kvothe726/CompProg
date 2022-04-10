// send in total length of strings for constructor not count of strings.
struct triest
{
	int psz;
	vector<int> cnt,len;
	vector<map<char, int>> to;

	triest() { // we need to initiate with sum of lengths of strings
		cnt.resize(1,0);
		len.resize(1,0);
		to.resize(1);
		psz = 1;
	}

	void add(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(!to[u].count(c)) {
                cnt.emplace_back(0);
                len.emplace_back(0);
                to.emplace_back();
                len[psz] = len[u] + 1; 
                to[u][c] = psz++;
            }
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

struct triest
{
	int psz;
	vector<int> cnt, len;
    vector<array<int,2>> to;

	triest() {
        cnt.assign(1,0);
        len.assign(1,0);
        to.assign(1,array<int,2>({-1,-1}));
		psz = 1; 
	}

	void add(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(to[u][c-'0']==-1){ 
				cnt.emplace_back(0);
                len.emplace_back(0);
                to.emplace_back(array<int,2>({-1,-1}));
                len[psz] = len[u] + 1; 
                to[u][c-'0'] = psz++;
            }
			u = to[u][c-'0']; cnt[u]++;
		}
	}

	void del(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(to[u][c-'0']==-1) return;
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
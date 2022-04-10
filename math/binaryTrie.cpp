struct triest
{
	int psz;
	vector<int> cnt, len;
    vector<vector<int>> to;

	triest() {
        cnt.assign(1,0);
        len.assign(1,0);
        to.assign(1,vector<int>(2,-1));
		psz = 1; 
	}

	void add(string s)
	{
		int u = 0;
		for(char c: s)
		{
			if(to[u][c-'0']==-1){ 
                len.emplace_back();
                to.emplace_back(vector<int>(2,-1));
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
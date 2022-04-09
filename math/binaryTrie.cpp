#include <bits/stdc++.h>

using namespace std;

struct trie
{
	int psz;
	vector<int> cnt, len;
    	vector<vector<int>> to;

	trie(int n) {
		int nodes = (n+5)*31;
		cnt.resize(nodes);
		len.resize(nodes);
		to.assign(nodes,vector<int>(2,-1));
		psz = 1; 
	}

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

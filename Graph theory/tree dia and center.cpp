struct TreeDiameter {
    int n, dist[MX], pre[MX];
    vector <int> adj[MX];

    void addEdge(int a, int b) {
        adj[a].pb(b), adj[b].pb(a);
    }

    void dfs(int cur) {
        for (int i: adj[cur]) if (i != pre[cur]) {
            pre[i] = cur;
            dist[i] = dist[cur]+1;
            dfs(i);
        }
    }

    void genDist(int cur) {
        memset(dist,0,sizeof dist);
        pre[cur] = -1;
        dfs(cur);
    }

    int diameterLength() {
        genDist(1);
        int bes = 0; for(int i=1;i<=n;i++) if (dist[i] > dist[bes]) bes = i;
        genDist(bes); for(int i=1;i<=n;i++) if (dist[i] > dist[bes]) bes = i;
        return dist[bes];
    }

    vector <int> genCenter() {
        int t = diameterLength();
        int bes = 0; for(int i=1;i<=n;i++) if (dist[i] > dist[bes]) bes = i;

        for(int i=0;i<t/2;i++) bes = pre[bes];
        if (t&1) return {bes,pre[bes]};
        return {bes};
    }
};

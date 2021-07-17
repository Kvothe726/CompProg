// pass zero indexed graph and edges

struct TreeDiameter {
    int n;
    vector<int> dist, pre;
    vector<vector <int>> adj;

    TreeDiameter(vector<vector<int>> g):adj(g){
        int n = adj.size();
        dist.assign(n,0);
        pre.resize(n);
    }

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
        pre[cur] = -1;
        dfs(cur);
    }

    int diameterLength() {
        genDist(0);
        int bes = 0; for(int i=0;i<n;i++) if (dist[i] > dist[bes]) bes = i;
        genDist(bes); for(int i=0;i<n;i++) if (dist[i] > dist[bes]) bes = i;
        return dist[bes];
    }

    vector <int> genCenter() {
        int t = diameterLength();
        int bes = 0; for(int i=0;i<n;i++) if (dist[i] > dist[bes]) bes = i;

        for(int i=0;i<t/2;i++) bes = pre[bes];
        if (t&1) return {bes,pre[bes]};
        return {bes};
    }
};

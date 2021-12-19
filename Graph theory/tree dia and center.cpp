// pass zero indexed graph and edges

class TreeDiameter {
public:
    int n;
    vector<int> dist, pre;
    vector<vector <int>> adj;

    TreeDiameter(vector<vector<int>> g):adj(g){
        n = adj.size();
        pre.resize(n);
    }

    void addEdge(int a, int b) {
        adj[a].push_back(b), adj[b].push_back(a);
    }

    void dfs(int cur) {
        for (int i: adj[cur]) if (i != pre[cur]) {
            pre[i] = cur;
            dist[i] = dist[cur]+1;
            dfs(i);
        }
    }

    void genDist(int cur) {
        dist.assign(n,0);
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
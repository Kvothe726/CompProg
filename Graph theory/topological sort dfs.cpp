class diGraph{
public:
	int n;
    vector<vector<int>> g;
    vector<int> used, ord;
    bool cyc = false;

    diGraph(int n):n(n){
        g.resize(n);
    }
    void add_edge(int u, int v){
        g[u].push_back(v);
    }

    void dfs(int v){
      used[v] = 1;
      for (int u : g[v]){
        if (used[u] == 0)
          dfs(u);
        else if (used[u] == 1)
          cyc = true;
        if (cyc)
          return;
      }
      used[v] = 2;
      ord.push_back(v);
    }

    vector<int> topological_sort(){
        cyc = false;
        used.assign(n, 0);
        ord.clear();
        for(int i=0;i<n;i++) if (!used[i]){
            dfs(i);
            if (cyc){
                return {};
            }
        }
        reverse(ord.begin(), ord.end());
        return ord;
    }
};

class kosaraju{
    void dfs(const vector<vector<int>> &graph, vector<bool> &used, vector<int> &res, int u) {
        used[u] = true;
        for (int v : graph[u])
            if (!used[v])
                dfs(graph, used, res, v);
        res.push_back(u);
    }
    vector<vector<int>> graph,components;

public:
    kosaraju(vector<vector<int>> g):graph(g){
    }

    // Get strongly connected components
    // each index 'i' contains list of all the actual vertices
    vector<vector<int>> scc() {
        int n = graph.size();
        vector<bool> used(n);
        vector<int> order;
        for (int i = 0; i < n; i++)
            if (!used[i])
                dfs(graph, used, order, i);

        vector<vector<int>> reverseGraph(n);
        for (int i = 0; i < n; i++)
            for (int j : graph[i])
                reverseGraph[j].push_back(i);

        components.clear();
        fill(used.begin(), used.end(), false);
        reverse(order.begin(), order.end());

        for (int u : order)
            if (!used[u]) {
                vector<int> component;
                dfs(reverseGraph, used, component, u);
                components.push_back(component);
            }

        return components;
    }

    // DAG of strongly connected components
    // 0,1,2,..c vertices of the condensed graph are in topological order defaultly.
    vector<vector<int>> scc_graph() {
        scc();
        vector<int> comp(graph.size());
        for (int i = 0; i < components.size(); i++)
            for (int u : components[i])
                comp[u] = i;
        vector<vector<int>> g(components.size());
        #warning using unordered set careful for hacks.
        unordered_set<long long> edges;
        for (int u = 0; u < graph.size(); u++)
            for (int v : graph[u])
                if (comp[u] != comp[v] && edges.insert(((long long)comp[u] << 32) + comp[v]).second)
                    g[comp[u]].push_back(comp[v]);
        return g;
    }
};
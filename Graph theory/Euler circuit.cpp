// can contain multiple edges, don't know about self loops though
// 0-indexed
// can be disconnected
class eulercircuit{
    int n;
    vector<multiset<int>> g;
public:
    eulercircuit(vector<vector<int>> adj){
        n = adj.size();
        g.resize(n);
        for(int i=0;i<n;i++){
            g[i].insert(adj[i].begin(), adj[i].end());
        }
    }

    vector<vector<int>> tour(){
        for(int i=0;i<n;i++){
            assert((g[i].size()%2) == 0);
        }

        vector<bool> vis(n,0);
        vector<vector<int>> ans;

        for(int i=0;i<n;i++){
            if(vis[i]){
                continue;
            }
            stack<int> st;
            st.push(i);
            vector<int> res;

            while (!st.empty()) {
                int v = st.top();
                int i;
                for (i = 0; i < n; ++i)
                    if (g[v].find(i)!=g[v].end())
                        break;
                if (i == n) {
                    res.push_back(v);
                    vis[v] = 1;
                    st.pop();
                } else {
                    g[v].erase(g[v].find(i));
                    g[i].erase(g[i].find(v));
                    st.push(i);
                }
            }

            ans.emplace_back(res);
        }
        return ans;
    }
};
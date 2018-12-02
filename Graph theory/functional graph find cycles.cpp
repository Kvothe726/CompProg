/*
    Remember functional graphs contain non intersecting cycles. That's the reason we are able to clearly separate cycles.

*/

vector< vector<int> > cycles;  // contains all the cycles

vector<char> used;
vector<int> path;

void dfs(int v) {
    path.push_back(v);
    used[v] = 1;

    int to = a[v];
    if(used[to] != 2) {
        if(used[to] == 1) {
            cycles.emplace_back();

            int id = sz(path) - 1;
            while(path[id] != to)
                cycles.back().push_back(path[id--]);
            cycles.back().push_back(to);
        } else
            dfs(to);
    }
    path.pop_back();
    used[v] = 2;
}

void solve() {
    used.assign(n, 0);

    forn(i, n) {
        if (!used[i])
            dfs(i);
    }
    return;
}

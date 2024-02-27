struct SCC {
    int n;
    vector<vector<int>> G;
    vector<int> dfn, low, id, stk;
    int scc{}, _t{};
    SCC(int _n) : n{_n}, G(_n) {}
    void dfs(int u) {
        dfn[u] = low[u] = _t++;
        stk.push_back(u);
        for (int v : G[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else if (id[v] == -1) {
                chmin(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int t;
            do {
                t = stk.back();
                stk.pop_back();
                id[t] = scc;
            } while (t != u);
            scc++;
        }
    }
    void work() {
        dfn.assign(n, -1);
        low.assign(n, -1);
        id.assign(n, -1);
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) {
                dfs(i);
            }
    }
};
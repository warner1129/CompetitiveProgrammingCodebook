struct SCC {
    int n;
    vector<vector<int>> G;
    vector<int> dfn, low, id;
    int scc{};
    SCC(int _n) : n{_n}, G(_n) {}
    void add_edge(int u, int v) {
        G[u].push_back(v);
    }
    void build() {
        dfn.assign(n, -1);
        low.assign(n, -1);
        id.assign(n, -1);
        vector<int> stk;
        int _t = 0;
        function<void(int)> dfs = [&](int u) {
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
        };
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) dfs(i);
    }
};

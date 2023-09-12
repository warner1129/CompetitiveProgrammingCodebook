struct TwoSAT {
    vector<vector<int>> G;
    int n;
    TwoSAT(int _n) : n(_n), G(_n * 2) {}
    int ne(int x) { return x < n ? x + n : x - n; }
    void add_edge(int u, int v) { // u or v
        G[ne(u)].push_back(v);
        G[ne(v)].push_back(u);
    }
    vector<int> solve() {
        vector<int> ans(n * 2, -1), id(n * 2), stk, \
            low(n * 2), dfn(n * 2), vis(n * 2);
        int _t = 0, scc_cnt = 0;
        function<void(int)> dfs = [&](int u) {
            dfn[u] = low[u] = _t++;
            stk.push_back(u);
            vis[u] = 1;
            for (int v : G[u]) {
                if (!vis[v])
                    dfs(v), chmin(low[u], low[v]);
                else if (vis[v] == 1)
                    chmin(low[u], dfn[v]);
            }
            if (dfn[u] == low[u]) {
                for (int x = -1; x != u; ) {
                    x = stk.back(); stk.pop_back();
                    vis[x] = 2, id[x] = scc_cnt;
                    if (ans[x] == -1) {
                        ans[x] = 1;
                        ans[ne(x)] = 0;
                    }
                }
                scc_cnt++;
            }
        };
        for (int i = 0; i < n + n; i++)
            if (!vis[i]) dfs(i);
        for (int i = 0; i < n; i++)
            if (id[i] == id[ne(i)])
                return {};
        ans.resize(n);
        return ans;
    }
};
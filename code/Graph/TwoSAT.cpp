struct TwoSat {
    int n;
    vector<vector<int>> G;
    vector<bool> ans;
    vector<int> id, dfn, low, stk;
    TwoSat(int n) : n(n), G(2 * n), ans(n), 
        id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1) {}
    void addClause(int u, bool f, int v, bool g) { // (u = f) or (v = g)
        G[2 * u + !f].push_back(2 * v + g);
        G[2 * v + !g].push_back(2 * u + f);
    } /* SPLIT-HASH */
    void addImply(int u, bool f, int v, bool g) { // (u = f) -> (v = g)
        G[2 * u + f].push_back(2 * v + g);
        G[2 * v + !g].push_back(2 * u + !f);
    } /* SPLIT-HASH */
    int cur = 0, scc = 0;
    void dfs(int u) {
        stk.push_back(u);
        dfn[u] = low[u] = cur++;
        for (int v : G[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else if (id[v] == -1) {
                chmin(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                id[x] = scc;
            } while (x != u);
            scc++;
        }
    } /* SPLIT-HASH */
    bool satisfiable() {
        for (int i = 0; i < n * 2; i++)
            if (dfn[i] == -1) {
                dfs(i);
            }
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) {
                return false;
            }
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
};

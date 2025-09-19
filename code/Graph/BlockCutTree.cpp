struct BlockCutTree {
    int n;
    vector<vector<int>> adj;
    BlockCutTree(int _n) : n(_n), adj(_n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pair<int, vector<pair<int, int>>> work() {
        vector<int> dfn(n, -1), low(n), stk;
        vector<pair<int, int>> edg;
        int cnt = 0, cur = 0;
        function<void(int)> dfs = [&](int x) {
            stk.push_back(x);
            dfn[x] = low[x] = cur++;
            for (auto y : adj[x]) {
                if (dfn[y] == -1) {
                    dfs(y);
                    low[x] = min(low[x], low[y]);
                    if (low[y] == dfn[x]) {
                        int v;
                        do {
                            v = stk.back();
                            stk.pop_back();
                            edg.emplace_back(n + cnt, v);
                        } while (v != y);
                        edg.emplace_back(x, n + cnt);
                        cnt++;
                    }
                } else {
                    low[x] = min(low[x], dfn[y]);
                }
            }
        };
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                stk.clear();
                dfs(i);
            }
        }
        return {cnt, edg};
    }
};

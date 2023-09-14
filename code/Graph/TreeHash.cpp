u64 TreeHash(const vector<vector<int>> &G) {
    const int n = G.size();
    vector<int> cen;
    vector<u64> pw(n, 1);
    for (int i = 1; i < n; i++) pw[i] = pw[i - 1] * u64(1e9 + 123);
    auto dfs = [&](auto self, int u, int fa) -> int {
        int siz = 1;
        bool f = true;
        for (int v : G[u]) if (v != fa) {
            int s = self(self, v, u);
            f &= (s * 2 <= n);
            siz += s;
        }
        f &= ((n - siz) * 2 <= n);
        if (f) cen.push_back(u);
        return siz;
    }; dfs(dfs, 0, -1);
    auto cal = [&](auto self, int u, int fa) -> pair<u64, int> {
        vector<pair<u64, int>> U;
        int siz = 1;
        u64 h = G[u].size();
        for (int v : G[u]) if (v != fa) {
            U.push_back(self(self, v, u));
        }
        sort(all(U));
        for (auto [v, s] : U) {
            h = h * pw[s] + v;
            siz += s;
        }
        return {h, siz};
    };
    vector<u64> H;
    for (int c : cen) H.push_back(cal(cal, c, -1).ff);
    return ranges::min(H);
};
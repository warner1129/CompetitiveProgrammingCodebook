struct CenDec {
    vector<vector<int>> C;
    vector<int> pa, ord;
    vector<bool> vis;
    CenDec(int n, const vector<vector<int>> &G) : C(n), pa(n, -1), vis(n) {
        vector<int> siz(n);
        function<int(int, int)> getsiz = [&](int u, int f) {
            siz[u] = 1;
            for (int v : G[u]) if (v != f and !vis[v])
                siz[u] += getsiz(v, u);
            return siz[u];
        };
        function<int(int, int, int)> find = [&](int u, int f, int s) {
            for (int v : G[u]) if (v != f and !vis[v])
                if (siz[v] * 2 >= s) return find(v, u, s);
            return u;
        };
        function<int(int)> build = [&](int u) -> int {
            u = find(u, u, getsiz(u, u));
            ord.push_back(u);
            vis[u] = 1;
            for (int v : G[u]) if (!vis[v]) {
                C[u].push_back(build(v));
                pa[C[u].back()] = u;
            }
            vis[u] = 0;
            return u;
        };
        ord.reserve(n);
        build(0);
    }
};
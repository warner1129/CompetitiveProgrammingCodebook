struct CenDec {
    vector<vector<pair<int, i64>>> G;
    vector<vector<i64>> pdis;
    vector<int> pa, ord, siz;
    vector<bool> vis;
    int getsiz(int u, int f) {
        siz[u] = 1;
        for (auto [v, w] : G[u]) if (v != f and !vis[v])
            siz[u] += getsiz(v, u);
        return siz[u];
    }
    int find(int u, int f, int s) {
        for (auto [v, w] : G[u]) if (v != f and !vis[v])
            if (siz[v] * 2 >= s) return find(v, u, s);
        return u;
    };
    void caldis(int u, int f, i64 dis) {
        pdis[u].push_back(dis);
        for (auto [v, w] : G[u]) if (v != f and !vis[v]) {
            caldis(v, u, dis + w);
        }
    }
    int build(int u = 0) {
        u = find(u, u, getsiz(u, u));
        ord.push_back(u);
        vis[u] = 1;
        for (auto [v, w] : G[u]) if (!vis[v]) {
            pa[build(v)] = u;
        }
        caldis(u, -1, 0); // if need
        vis[u] = 0;
        return u;
    };
    CenDec(int n) : G(n), pa(n, -1), vis(n), siz(n), pdis(n) {}
};
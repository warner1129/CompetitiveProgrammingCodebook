struct CenDec {
    vector<vector<pair<int, int>>> anc;
    vector<int> Mdis;
    CenDec(const vector<vector<int>> &G) : anc(G.size()), Mdis(G.size(), INF) {
        const int n = G.size(); 
        vector<int> siz(n);
        vector<bool> vis(n);
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
        function<void(int, int, int, int)> caldis = [&](int u, int f, int a, int d) {
            anc[u].emplace_back(a, d);
            for (int v : G[u]) if (v != f and !vis[v])
                caldis(v, u, a, d + 1);
        };
        function<void(int)> build = [&](int u) {
            u = find(u, u, getsiz(u, u));
            vis[u] = 1;
            for (int v : G[u]) if (!vis[v]) {
                caldis(v, u, u, 1);
                build(v);
            }
            vis[u] = 0;
        };
        build(0);
    }
    void add(int p) {
        Mdis[p] = 0;
        for (auto [v, d] : anc[p])
            chmin(Mdis[v], d);
    }
    int que(int p) {
        int r = Mdis[p];
        for (auto [v, d] : anc[p])
            chmin(r, Mdis[v] + d);
        return r;
    }
};
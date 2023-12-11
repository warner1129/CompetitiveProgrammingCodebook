struct HLD {
    int n;
    vector<int> siz, top, dep, pa, in, out, seq;
    vector<vector<int>> G;
    HLD(int n) : n(n), G(n), siz(n), top(n), 
        dep(n), pa(n), in(n), out(n), seq(n) {}
    int cur{};
    void addEdge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void work(int root = 0) {
        cur = 0;
        top[root] = root;
        dep[root] = 0;
        pa[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (pa[u] != -1) {
            G[u].erase(find(all(G[u]), pa[u]));
        }
        siz[u] = 1;
        for (auto &v : G[u]) {
            pa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[G[u][0]]) {
                swap(v, G[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (int v : G[u]) {
            top[v] = (v == G[u][0] ? top[u] : v);
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = pa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
    int dist(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    int jump(int x, int k) {
        if (dep[x] < k) return -1;
        int d = dep[x] - k;
        while (dep[top[x]] > d) {
            x = pa[top[x]];
        }
        return seq[in[x] - dep[x] + d];
    }
    bool isAnc(int x, int y) {
        return in[x] <= in[y] and in[y] < out[x];
    }
    int rootPar(int r, int x) {
        if (r == x) return r;
        if (!isAnc(x, r)) return pa[x];
        auto it = upper_bound(all(G[x]), r, [&](int a, int b) -> bool {
            return in[a] < in[b];
        }) - 1;
        return *it;
    }
    int rootSiz(int r, int x) {
        if (r == x) return n;
        if (!isAnc(x, r)) return siz[x];
        return n - siz[rootPar(r, x)];
    }
    int rootLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

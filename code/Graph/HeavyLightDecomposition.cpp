struct HLD {
    int n;
    vector<int> siz, dep, pa, in, out, seq, top, tail;
    vector<vector<int>> G;
    HLD(int n) : n(n), G(n), siz(n), dep(n), pa(n), 
        in(n), out(n), top(n), tail(n) {}
    void build(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        pa[root] = -1;
        dfs1(root);
        dfs2(root);
    } /* SPLIT-HASH */
    void dfs1(int u) {
        erase(G[u], pa[u]);
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
    } /* SPLIT-HASH */
    void dfs2(int u) {
        in[u] = seq.size();
        seq.push_back(u);
        tail[u] = u;
        for (int v : G[u]) {
            top[v] = (v == G[u][0] ? top[u] : v);
            dfs2(v);
            if (v == G[u][0]) {
                tail[u] = tail[v];
            }
        }
        out[u] = seq.size();
    } /* SPLIT-HASH */
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = pa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    } /* SPLIT-HASH */
    int dist(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    } /* SPLIT-HASH */
    int jump(int x, int k) {
        if (dep[x] < k) return -1;
        int d = dep[x] - k;
        while (dep[top[x]] > d) {
            x = pa[top[x]];
        }
        return seq[in[x] - dep[x] + d];
    } /* SPLIT-HASH */
    bool isAnc(int x, int y) {
        return in[x] <= in[y] and in[y] < out[x];
    } /* SPLIT-HASH */
    int rootPar(int r, int x) {
        if (r == x) return r;
        if (!isAnc(x, r)) return pa[x];
        auto it = upper_bound(all(G[x]), r, [&](int a, int b) -> bool {
            return in[a] < in[b];
        }) - 1;
        return *it;
    } /* SPLIT-HASH */
    int rootSiz(int r, int x) {
        if (r == x) return n;
        if (!isAnc(x, r)) return siz[x];
        return n - siz[rootPar(r, x)];
    } /* SPLIT-HASH */
    int rootLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    } /* SPLIT-HASH */
};

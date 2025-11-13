struct Tree {
    int n, lgN;
    vector<vector<int>> G;
    vector<vector<int>> st;
    vector<int> in, out, dep, pa, seq;
    Tree(int n) : n(n), G(n), in(n), out(n), dep(n), pa(n, -1) {}
    int cmp(int a, int b) {
        return dep[a] < dep[b] ? a : b;
    }
    void dfs(int u) {
        erase(G[u], pa[u]);
        in[u] = seq.size();
        seq.push_back(u);
        for (int v : G[u]) {
            dep[v] = dep[u] + 1;
            pa[v] = u;
            dfs(v);
        }
        out[u] = seq.size();
    }
    void build() {
        seq.reserve(n);
        dfs(0);
        lgN = __lg(n);
        st.assign(lgN + 1, vector<int>(n));
        st[0] = seq;
        for (int i = 0; i < lgN; i++)
            for (int j = 0; j + (2 << i) <= n; j++)
                st[i + 1][j] = cmp(st[i][j], st[i][j + (1 << i)]);
    }  /* SPLIT-HASH */
    int inside(int x, int y) {
        return in[x] <= in[y] and in[y] < out[x];
    }  /* SPLIT-HASH */
    int lca(int x, int y) {
        if (x == y) return x;
        if ((x = in[x] + 1) > (y = in[y] + 1))
            swap(x, y);
        int h = __lg(y - x);
        return pa[cmp(st[h][x], st[h][y - (1 << h)])];
    }  /* SPLIT-HASH */
    int dist(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }  /* SPLIT-HASH */
    int rootPar(int r, int x) {
        if (r == x) return -1;
        if (!inside(x, r)) return pa[x];
        return *--upper_bound(all(G[x]), r,
            [&](int a, int b) -> bool {
                return in[a] < in[b];
            });
    }  /* SPLIT-HASH */
    int size(int x) { return out[x] - in[x]; }
    int rootSiz(int r, int x) {
        if (r == x) return n;
        if (!inside(x, r)) return size(x);
        return n - size(rootPar(r, x));
    }  /* SPLIT-HASH */
    int rootLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    } /* SPLIT-HASH */
    vector<int> virTree(vector<int> ver) {
        sort(all(ver), [&](int a, int b) {
            return in[a] < in[b];
        });
        for (int i = ver.size() - 1; i > 0; i--)
            ver.push_back(lca(ver[i], ver[i - 1]));
        sort(all(ver), [&](int a, int b) {
            return in[a] < in[b];
        });
        ver.erase(unique(all(ver)), ver.end());
        return ver;
    }
};

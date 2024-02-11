struct LCA {
    int n, lgN;
    vector<vector<int>> G, st;
    vector<int> in, out, dep, pa, seq;
    LCA(int n) : n(n), G(n), in(n), out(n), dep(n), pa(n, -1) {}
    int cmp(int a, int b) {
        return dep[a] < dep[b] ? a : b;
    }
    void dfs(int u) {
        in[u] = seq.size();
        seq.push_back(u);
        for (int v : G[u]) if (v != pa[u]) {
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
    }
    int inside(int x, int y) {
        return in[x] <= in[y] and in[y] < out[x];
    }
    int lca(int x, int y) {
        if (x == y) return x;
        if ((x = in[x] + 1) > (y = in[y] + 1))
            swap(x, y);
        int h = __lg(y - x);
        return pa[cmp(st[h][x], st[h][y - (1 << h)])];
    }
    int dist(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
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
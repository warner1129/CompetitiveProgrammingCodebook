struct Tree {
    int n, lgN;
    vector<vector<int>> G, st;
    vector<int> in, out, dep, pa, seq;
    Tree(int n) : n(n), G(n), in(n), out(n), dep(n), pa(n, -1) {}
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
    void inplace_virTree(vector<int> &ver) { // O(n), need sort before
        vector<int> ex;
        for (int i = 0; i + 1 < ver.size(); i++)
            if (!inside(ver[i], ver[i + 1]))
                ex.push_back(lca(ver[i], ver[i + 1]));
        vector<int> stk, pa(ex.size(), -1);
        for (int i = 0; i < ex.size(); i++) {
            int lst = -1;
            while (stk.size() and in[ex[stk.back()]] >= in[ex[i]]) {
                lst = stk.back();
                stk.pop_back();
            }
            if (lst != -1) pa[lst] = i;
            if (stk.size()) pa[i] = stk.back();
            stk.push_back(i);
        }
        vector<bool> vis(ex.size());
        auto dfs = [&](auto self, int u) -> void {
            vis[u] = 1;
            if (pa[u] != -1 and !vis[pa[u]]) 
                self(self, pa[u]);
            if (ex[u] != ver.back())
                ver.push_back(ex[u]);
        };
        const int s = ver.size();
        for (int i = 0; i < ex.size(); i++)
            if (!vis[i]) dfs(dfs, i);
        inplace_merge(ver.begin(), ver.begin() + s, ver.end(),
                [&](int a, int b) { return in[a] < in[b]; });
        ver.erase(unique(all(ver)), ver.end());
    }
};
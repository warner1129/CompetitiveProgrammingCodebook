// bel[x]: x is belong bel[x]-th jellyfish
// len[x]: cycle length of x-th jellyfish
// ord[x]: order of x in cycle (x == root[x])
struct FunctionalGraph {
    int n, _t = 0;
    vector<vector<int>> G;
    vector<int> f, bel, dep, ord, root, in, out, len;
    FunctionalGraph(int n) : n(n), G(n), root(n),
         bel(n, -1), dep(n), ord(n), in(n), out(n) {}
    void dfs(int u) {
        in[u] = _t++;
        for (int v : G[u]) if (bel[v] == -1) {
            dep[v] = dep[u] + 1;
            root[v] = root[u];
            bel[v] = bel[u];
            dfs(v);
        }
        out[u] = _t;
    }; /* SPLIT-HASH */
    void build(const auto &_f) {
        f = _f;
        for (int i = 0; i < n; i++)
            G[f[i]].push_back(i);
        vector<int> vis(n, -1);
        for (int i = 0; i < n; i++) if (vis[i] == -1) {
            int x = i;
            while (vis[x] == -1) {
                vis[x] = i;
                x = f[x];
            }
            if (vis[x] != i) continue;
            int s = x, l = 0;
            do {
                bel[x] = len.size();
                ord[x] = l++;
                root[x] = x;
                x = f[x];
            } while (x != s);
            len.push_back(l);
        }
        for (int i = 0; i < n; i++)
            if (root[i] == i)
                dfs(i);
    } /* SPLIT-HASH */
    int dist(int x, int y) { // x -> y
        if (bel[x] != bel[y])
            return -1;
        if (dep[x] < dep[y])
            return -1;
        if (dep[y] != 0) {
            if (in[y] <= in[x] and in[x] < out[y])
                return dep[x] - dep[y];
            return -1;
        }
        return dep[x] + (ord[y] - ord[root[x]] + len[bel[x]]) % len[bel[x]];
    }
};

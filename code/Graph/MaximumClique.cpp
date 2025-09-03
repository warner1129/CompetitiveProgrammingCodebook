constexpr size_t kN = 150;
using bits = bitset<kN>;
struct MaxClique {
    bits G[kN], cs[kN];
    int ans, sol[kN], q, cur[kN], d[kN], n;
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) G[i].reset();
    }
    void addEdge(int u, int v) {
        G[u][v] = G[v][u] = 1;
    }
    void preDfs(vector<int> &v, int i, bits mask) {
        if (i < 4) {
            for (int x : v) d[x] = (G[x] & mask).count();
            sort(all(v), [&](int x, int y) {
                return d[x] > d[y];
            });
        }
        vector<int> c(v.size());
        cs[1].reset(), cs[2].reset();
        int l = max(ans - q + 1, 1), r = 2, tp = 0, k;
        for (int p : v) {
            for (k = 1;
                (cs[k] & G[p]).any(); ++k);
            if (k >= r) cs[++r].reset();
            cs[k][p] = 1;
            if (k < l) v[tp++] = p;
        }
        for (k = l; k < r; ++k)
            for (auto p = cs[k]._Find_first(); p < kN; p = cs[k]._Find_next(p))
                v[tp] = p, c[tp] = k, ++tp;
        dfs(v, c, i + 1, mask);
    } /* SPLIT-HASH */
    void dfs(vector<int> &v, vector<int> &c, int i, bits mask) {
        while (!v.empty()) {
            int p = v.back();
            v.pop_back();
            mask[p] = 0;
            if (q + c.back() <= ans) return;
            cur[q++] = p;
            vector<int> nr;
            for (int x : v)
                if (G[p][x]) nr.push_back(x);
            if (!nr.empty()) preDfs(nr, i, mask & G[p]);
            else if (q > ans) ans = q, copy_n(cur, q, sol);
            c.pop_back();
            --q;
        }
    }
    int solve() {
        vector<int> v(n);
        iota(all(v), 0);
        ans = q = 0;
        preDfs(v, 0, bits(string(n, '1')));
        return ans;
    }
} cliq;

struct DSU {
    vector<int> f, s;
    int cc;
    DSU(int n) : f(n, -1), s(n, 1), cc(n) {}
    int find(int x) { return f[x] < 0 ? x : f[x] = find(f[x]); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        s[y] += s[x];
        f[x] = y;
        cc--;
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return s[find(x)]; }
};

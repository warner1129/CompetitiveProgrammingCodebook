template<class T>
struct DSU {
    vector<T> tag;
    vector<int> f, siz, stk;
    int cc;
    DSU(int n) : f(n, -1), siz(n, 1), tag(n), cc(n) {}
    int find(int x) { return f[x] < 0 ? x : find(f[x]); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (siz[x] > siz[y]) swap(x, y);
        f[x] = y;
        siz[y] += siz[x];
        tag[x] = tag[x] - tag[y];
        stk.push_back(x);
        cc--;
        return true;
    }
    void apply(int x, T s) {
        x = find(x);
        tag[x] = tag[x] + s;
    }
    void undo() {
        int x = stk.back();
        int y = f[x];
        stk.pop_back();
        tag[x] = tag[x] + tag[y];
        siz[y] -= siz[x];
        f[x] = -1;
        cc++;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return siz[find(x)]; }
};
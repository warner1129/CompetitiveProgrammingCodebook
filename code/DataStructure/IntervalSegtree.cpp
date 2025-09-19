struct Seg {
    Seg *ls, *rs;
    int l, r;
    vector<int> f, g;
    // f : intervals where covering [l, r]
    // g : intervals where interset with [l, r]
    Seg(int _l, int _r) : l{_l}, r{_r} {
        int mid = (l + r) >> 1;
        if (r - l == 1) return;
        ls = new Seg(l, mid);
        rs = new Seg(mid, r);
    }
    void insert(int x, int y, int id) {
        if (y <= l or r <= x) return;
        g.push_back(id);
        if (x <= l and r <= y) {
            f.push_back(id);
            return;
        }
        ls->insert(x, y, id);
        rs->insert(x, y, id);
    }
    void fix() {
        while (!f.empty() and use[f.back()]) f.pop_back();
        while (!g.empty() and use[g.back()]) g.pop_back();
    }
    int query(int x, int y) {
        if (y <= l or r <= x) return -1;
        fix();
        if (x <= l and r <= y) {
            return g.empty() ? -1 : g.back();
        }
        return max({f.empty() ? -1 : f.back(), ls->query(x, y), rs->query(x, y)});
    }
};

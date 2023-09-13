struct Seg {
    Seg *ls{}, *rs{};
    int l, r;
    i64 sum{};
    Seg(Seg* p) { (*this) = *p; }
    Seg(int _l, int _r, const vector<int> &v) : l{_l}, r{_r} {
        if (r - l == 1) {
            sum = v[l];
            return;
        }
        int mid = l + r >> 1;
        ls = new Seg(l, mid, v);
        rs = new Seg(mid, r, v);
        pull();
    }
    void pull() {
        sum = ls->sum + rs->sum;
    }
    Seg* modify(int p, int v) {
        Seg* ret = new Seg(this);
        if (r - l == 1) {
            ret->sum = v;
            return ret;
        }
        if (p < (l + r >> 1)) ret->ls = ret->ls->modify(p, v);
        else ret->rs = ret->rs->modify(p, v);
        ret->pull();
        return ret;
    }
    i64 query(int x, int y) {
        if (y <= l or r <= x) return 0;
        if (x <= l and r <= y) return sum;
        return ls->query(x, y) + rs->query(x, y);
    }
};
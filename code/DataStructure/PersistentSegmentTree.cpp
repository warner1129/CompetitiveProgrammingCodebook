template <class S>
struct Seg {
    Seg *ls{}, *rs{};
    int l, r;
    S d{};
    Seg(Seg* p) { (*this) = *p; }
    Seg(int l, int r) : l(l), r(r) {
        if (r - l == 1) {
            d = {};
            return;
        }
        int mid = (l + r) / 2;
        ls = new Seg(l, mid);
        rs = new Seg(mid, r);
        pull();
    }
    void pull() {
        d = ls->d + rs->d;
    }
    Seg* set(int p, const S &x) {
        Seg* n = new Seg(this);
        if (r - l == 1) {
            n->d = x;
            return n;
        }
        int mid = (l + r) / 2;
        if (p < mid) {
            n->ls = ls->set(p, x);
        } else {
            n->rs = rs->set(p, x);
        }
        n->pull();
        return n;
    }
    S query(int x, int y) {
        if (y <= l or r <= x) return {};
        if (x <= l and r <= y) return d;
        return ls->query(x, y) + rs->query(x, y);
    }
};
struct Seg {
    Seg *ls{}, *rs{};
    int l, r;
    int nonz{}, cov{};
    Seg(int _l, int _r) : l(_l), r(_r) {
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        ls = new Seg(l, m);
        rs = new Seg(m, r);
    }
    int get() {
        return cov ? r - l : nonz;
    }
    void pull() {
        int t = min(ls->cov, rs->cov);
        ls->cov -= t;
        rs->cov -= t;
        cov += t;
        nonz = ls->get() + rs->get();
    }
    void push() {
        ls->cov += cov;
        rs->cov += cov;
        cov = 0;
    }
    void apply(int x, int y, int t) {
        if (y <= l or r <= x) {
            return;
        }
        if (x <= l and r <= y) {
            cov += t;
            assert(cov >= 0);
            return;
        }
        push();
        ls->apply(x, y, t);
        rs->apply(x, y, t);
        pull();
    }
};

template<class S, class T>
struct Seg {
    Seg<S, T> *ls{}, *rs{};
    int l, r;
    S d{};
    T f{};
    Seg(int _l, int _r, const vector<Info> &v) : l{_l}, r{_r} {
        if (r - l == 1) {
            d = v[l];
            return;
        }
        int mid = l + r >> 1;
        ls = new Seg(l, mid, v);
        rs = new Seg(mid, r, v);
        pull();
    }
    void upd(const T &g) {
        g(d), g(f);
    }
    void pull() {
        d = ls->d + rs->d;
    }
    void push() {
        ls->upd(f);
        rs->upd(f);
        f = T{};
    }
    S prod(int x, int y) {
        if (y <= l or r <= x) return S{};
        if (x <= l and r <= y) return d;
        push();
        return ls->prod(x, y) + rs->prod(x, y);
    }
    void apply(int x, int y, const T &g) {
        if (y <= l or r <= x) return;
        if (x <= l and r <= y) {
            upd(g);
            return;
        }
        push();
        ls->apply(x, y, g);
        rs->apply(x, y, g);
        pull();
    }
};
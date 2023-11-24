template<class S, class T>
struct Seg {
    Seg<S, T> *ls{}, *rs{};
    int l, r;
    S d{};
    T f{};
    Seg(int _l, int _r) : l{_l}, r{_r} {
        if (r - l == 1) {
            return;
        }
        int mid = (l + r) / 2;
        ls = new Seg(l, mid);
        rs = new Seg(mid, r);
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
    S query(int x, int y) {
        if (y <= l or r <= x) return S{};
        if (x <= l and r <= y) return d;
        push();
        return ls->query(x, y) + rs->query(x, y);
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
    void set(int p, const S &g) {
        if (p + 1 <= l or r <= p) return;
        if (r - l == 1) {
            d = g;
            return;
        }
        push();
        ls->set(p, g);
        rs->set(p, g);
        pull();
    }
    int findFirst(int x, int y, auto pred) {
        if (y <= l or r <= x or !pred(d)) return -1;
        if (r - l == 1) return l;
        push();
        int res = ls->findFirst(x, y, pred);
        return res == -1 ? rs->findFirst(x, y, pred) : res;
    }
    int findLast(int x, int y, auto pred) {
        if (y <= l or r <= x or !pred(d)) return -1;
        if (r - l == 1) return l;
        push();
        int res = rs->findLast(x, y, pred);
        return res == -1 ? ls->findLast(x, y, pred) : res;
    }
};

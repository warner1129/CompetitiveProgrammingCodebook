template<class S>
struct Seg {
    Seg<S> *ls{}, *rs{};
    int l, r;
    S d{};
    Seg(int _l, int _r) : l{_l}, r{_r} {
        if (r - l == 1) {
            return;
        }
        int mid = (l + r) / 2;
        ls = new Seg(l, mid);
        rs = new Seg(mid, r);
        pull();
    }
    void pull() { d = ls->d + rs->d; }
    S query(int x, int y) {
        if (y <= l or r <= x)
            return S{};
        if (x <= l and r <= y)
            return d;
        return ls->query(x, y) + rs->query(x, y);
    }
    void set(int p, const S &e) {
        if (p + 1 <= l or r <= p)
            return;
        if (r - l == 1) {
            d = e;
            return;
        }
        ls->set(p, e);
        rs->set(p, e);
        pull();
    }
    pair<int, S> findFirst(int x, int y, auto &&pred, S cur = {}) {
        if (y <= l or r <= x)
            return {-1, {}};
        if (x <= l and r <= y and !pred(cur + d))
            return {-1, cur + d};
        if (r - l == 1) 
            return {l, cur + d};
        auto res = ls->findFirst(x, y, pred, cur);
        return res.ft == -1 ? rs->findFirst(x, y, pred, res.sd) : res;
    }
    pair<int, S> findLast(int x, int y, auto &&pred, S cur = {}) {
        if (y <= l or r <= x)
            return {-1, {}};
        if (x <= l and r <= y and !pred(d + cur))
            return {-1, d + cur};
        if (r - l == 1)
            return {l, d + cur};
        auto res = rs->findLast(x, y, pred, cur);
        return res.ft == -1 ? ls->findLast(x, y, pred, res.sd) : res;
    }
};

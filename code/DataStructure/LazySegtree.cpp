template<class S, class T>
struct Seg {
    Seg *ls{}, *rs{}; S sum{}; T tag{}; int l, r;
    Seg(int _l, int _r) : l(_l), r(_r) {
        if (r - l == 1)
            return;
        int m = (l + r) / 2;
        ls = new Seg(l, m);
        rs = new Seg(m, r);
        pull();
    }
    void pull() { sum = ls->sum + rs->sum; }
    void push() {
        ls->apply(tag);
        rs->apply(tag);
        tag = T{};
    }
    void apply(const T &f) { f(tag); f(sum); }
    S query(int x, int y) {
        if (y <= l or r <= x)
            return {};
        if (x <= l and r <= y)
            return sum;
        push();
        return ls->query(x, y) + rs->query(x, y);
    }
    void apply(int x, int y, const T &f) {
        if (y <= l or r <= x)
            return;
        if (x <= l and r <= y)
            return apply(f);
        push();
        ls->apply(x, y, f);
        rs->apply(x, y, f);
        pull();
    } /* SPLIT-HASH */
    void set(int p, const S &e) {
        if (p < l or p >= r)
            return;
        if (r - l == 1)
            return sum = e, void();
        push();
        ls->set(p, e);
        rs->set(p, e);
        pull();
    }
    pair<int, S> findFirst(int x, int y, auto &&pred, S cur = {}) {
        if (y <= l or r <= x)
            return { -1, cur };
        if (x <= l and r <= y and !pred(cur + sum))
            return { -1, cur + sum };
        if (r - l == 1)
            return { l, cur + sum };
        push();
        auto L = ls->findFirst(x, y, pred, cur);
        if (L.ff != -1) return L;
        return rs->findFirst(x, y, pred, L.ss);
    }
    pair<int, S> findLast(int x, int y, auto &&pred, S cur = {}) {
        if (y <= l or r <= x)
            return { -1, cur };
        if (x <= l and r <= y and !pred(sum + cur))
            return { -1, sum + cur };
        if (r - l == 1)
            return { l, sum + cur };
        push();
        auto R = rs->findLast(x, y, pred, cur);
        if (R.ff != -1) return R;
        return ls->findLast(x, y, pred, R.ss);
    }
};

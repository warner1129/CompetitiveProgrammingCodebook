struct Line {
    // y = ax + b
    i64 a{0}, b{-inf<i64>};
    i64 operator()(i64 x) {
        return a * x + b;
    }
};
 
struct Seg {
    int l, r;
    Seg *ls{}, *rs{};
    Line f{};
    Seg(int l, int r) : l(l), r(r) {}
    void add(Line g) {
        int m = (l + r) / 2;
        if (g(m) > f(m)) {
            swap(g, f);
        }
        if (g.b == -inf<i64> or r - l == 1) {
            return;
        }
        if (g.a < f.a) {
            if (!ls) {
                ls = new Seg(l, m);
            }
            ls->add(g);
        } else {
            if (!rs) {
                rs = new Seg(m, r);
            }
            rs->add(g);
        }
    }
    i64 qry(i64 x) {
        if (f.b == -inf<i64>) {
            return -inf<i64>;
        }
        int m = (l + r) / 2;
        i64 y = f(x);
        if (x < m and ls) {
            chmax(y, ls->qry(x));
        } else if (x >= m and rs) {
            chmax(y, rs->qry(x));
        }
        return y;
    }
};
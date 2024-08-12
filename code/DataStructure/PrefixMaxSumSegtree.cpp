// O(Nlog^2N)!
const int kC = 1E6;
struct Seg {
    static Seg pool[kC], *top;
    Seg *ls{}, *rs{};
    int l, r;
    i64 sum = 0, rsum = 0, mx = 0;
    Seg() {}
    Seg(int _l, int _r, const vector<i64> &v) : l(_l), r(_r) {
        if (r - l == 1) {
            sum = mx = v[l];
            return;
        }
        int m = (l + r) / 2;
        ls = new (top++) Seg(l, m, v);
        rs = new (top++) Seg(m, r, v);
        pull();
    }
    i64 cal(i64 h) { // sigma i in [l, r) max(h, v[i])
        if (r - l == 1) {
            return max(mx, h);
        }
        if (mx <= h) {
            return h * (r - l);
        }
        if (ls->mx >= h) {
            return ls->cal(h) + rsum;
        }
        return h * (ls->r - ls->l) + rs->cal(h);
    }
    void pull() {
        rsum = rs->cal(ls->mx);
        sum = ls->sum + rsum;
        mx = max(ls->mx, rs->mx);
    }
    void set(int p, i64 h) {
        if (r - l == 1) {
            sum = mx = h;
            return;
        }
        int m = (l + r) / 2;
        if (p < m) {
            ls->set(p, h);
        } else {
            rs->set(p, h);
        }
        pull();
    }
    i64 query(int p, i64 h) { // sigma i in [0, p) max(h, v[i])
        if (p <= l) {
            return 0;
        }
        if (p >= r) {
            return cal(h);
        }
        return ls->query(p, h) + rs->query(p, max(h, ls->mx));
    }
} Seg::pool[kC], *Seg::top = Seg::pool;
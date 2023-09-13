struct Line {
    i64 k, m; // y = k + mx;
    Line() : k{INF}, m{} {}
    Line(i64 _k, i64 _m) : k(_k), m(_m) {}
    i64 get(i64 x) {
        return k + m * x;
    }
}; 
struct Seg {
    Seg *ls{}, *rs{};
    int l, r, mid;
    Line line{};
    Seg(int _l, int _r) : l(_l), r(_r), mid(_l + _r >> 1) {
        if (r - l == 1) return;
        ls = new Seg(l, mid);
        rs = new Seg(mid, r);
    }
    void insert(Line L) {
        if (line.get(mid) > L.get(mid)) 
            swap(line, L);
        if (r - l == 1) return;
        if (L.m < line.m) {
            rs->insert(L);
        } else {
            ls->insert(L);
        }
    }
    i64 query(int p) {
        if (p < l or r <= p) return INF;
        if (r - l == 1) return line.get(p);
        return min({line.get(p), ls->query(p), rs->query(p)});
    }
};
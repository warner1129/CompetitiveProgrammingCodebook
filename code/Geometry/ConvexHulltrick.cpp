int cycMin(int n, auto &&comp) {
    if (n == 1) return 0;
    int l = 0, r = n; bool f = comp(1, 0);
    while (r - l > 1) {
        int m = (l + r) / 2;
        ((comp(0, m) ? f : comp(m, (m + 1) % n)) ? r : l) = m;
    }
    return comp(l, r % n) ? l : r % n;
}  /* SPLIT-HASH */
struct Convex {
    int n;
    vector<Pt> C;
    vector<Pt>::iterator up;
    Convex(const vector<Pt> &_C) : C(_C), n(_C.size()) {
        C.push_back(C[0]);
        up = max_element(all(C));
    }
    int inside(const Pt &p, auto l, auto r, auto &&pred) {
        auto it = lower_bound(l, r, p, pred);
        int id = (it - C.begin()) % n;
        if (it == r) return id;
        if (it == l) return p == *it ? id : -1;
        int s = sgn(ori(it[-1], p, *it));
        if (s == 0) return id;
        return s == 1 ? -1 : n;
    }  /* SPLIT-HASH */
    int inside(const Pt &p) { 
        // -1:out, 0<=id<n:on edge C[id-1], C[id], n:in
        return min(inside(p, C.begin(), up + 1, less{}), 
                   inside(p, up, C.end(), greater{}));
    }  /* SPLIT-HASH */
    int tangentDir(const Pt &dir) {
        return cycMin(n, [&](int a, int b) {
            return (dir ^ C[a]) < (dir ^ C[b]);
        });
    }  /* SPLIT-HASH */
    array<int, 2> tangentPt(const Pt &p) {
        int i = inside(p);
        assert(i != n);
        if (i >= 0) return {
            (i + (p == C[i])) % n, (i - 1 + n) % n
        };
        auto get = [&](int s) {
            return cycMin(n, [&](int a, int b) {
                return sgn(ori(p, C[a], C[b])) == s;
            });
        };
        return {get(1), get(-1)};
    }  /* SPLIT-HASH */
    vector<int> intersect(const Line &L) {
    // Line A_x A_x+1 interset with L
        auto find = [&](int l, int r) -> int {
            if (r < l) r += n;
            int s = PtSide(C[l % n], L);
            return *ranges::partition_point(
                views::iota(l, r),
                [&](int m) {
                    return PtSide(C[m % n], L) == s;
                }) - 1;
        };
        int l = tangentDir(L.a - L.b), r = tangentDir(L.b - L.a);
        if (PtSide(C[l], L) * PtSide(C[r], L) >= 0) return {};
        return {find(l, r) % n, find(r, l) % n};
    }
};

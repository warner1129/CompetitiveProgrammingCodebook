vector<Pt> HPI(vector<Line> P) {
    const int n = P.size();
    sort(all(P), [&](Line L, Line R) -> bool {
        Pt u = L.b - L.a, v = R.b - R.a;
        bool f = Pt{sgn(u.ff), sgn(u.ss)} < Pt{};
        bool g = Pt{sgn(v.ff), sgn(v.ss)} < Pt{};
        if (f != g) return f < g;
        return (sgn(u ^ v) ? sgn(u ^ v) : PtSide(L.a, R)) > 0;
    });
    auto same = [&](Line L, Line R) {
        Pt u = L.b - L.a, v = R.b - R.a;
        return sgn(u ^ v) == 0 and sgn(u * v) == 1;
    };
    deque<Pt> inter;
    deque<Line> seg;
    for (int i = 0; i < n; i++) if (i == 0 or !same(P[i - 1], P[i])) {
        while (seg.size() >= 2 and PtSide(inter.back(), P[i]) == -1) {
            seg.pop_back(), inter.pop_back();
        }
        while (seg.size() >= 2 and PtSide(inter[0], P[i]) == -1) {
            seg.pop_front(), inter.pop_front();
        }
        if (!seg.empty()) inter.push_back(LineInter(seg.back(), P[i]));
        seg.push_back(P[i]);
    }
    while (seg.size() >= 2 and PtSide(inter.back(), seg[0]) == -1) {
        seg.pop_back(), inter.pop_back();
    }
    inter.push_back(LineInter(seg[0], seg.back()));
    return vector<Pt>(all(inter));
}
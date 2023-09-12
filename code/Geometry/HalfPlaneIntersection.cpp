vector<Pt> HPI(vector<Line> P) {
    const int n = P.size();
    sort(all(P), [&](Line L, Line R) -> bool {
        Pt u = L.b - L.a, v = R.b - R.a;
        bool f = Pt(sig(u.ff), sig(u.ss)) < Pt{};
        bool g = Pt(sig(v.ff), sig(v.ss)) < Pt{};
        if (f != g) return f < g;
        return (sig(u ^ v) ? sig(u ^ v) : sig(cro(L.a, R.a, R.b))) > 0;
    });
    auto Same = [&](Line L, Line R) {
        Pt u = L.b - L.a, v = R.b - R.a;
        return sig(u ^ v) == 0 and sig(u * v) == 1;
    };
    deque <Pt> inter;
    deque <Line> seg;
    for (int i = 0; i < n; i++) if (i == 0 or !Same(P[i - 1], P[i])) {
        while (seg.size() >= 2 and sig(cro(inter.back(), P[i].b, P[i].a)) == 1) {
            seg.pop_back(), inter.pop_back();
        }
        while (seg.size() >= 2 and sig(cro(inter[0], P[i].b, P[i].a)) == 1) {
            seg.pop_front(), inter.pop_front();
        }
        if (!seg.empty()) inter.push_back(Inter(seg.back(), P[i]));
        seg.push_back(P[i]);
    }
    while (seg.size() >= 2 and sig(cro(inter.back(), seg[0].b, seg[0].a)) == 1) {
        seg.pop_back(), inter.pop_back();
    }
    inter.push_back(Inter(seg[0], seg.back()));
    return vector<Pt>(all(inter));
}
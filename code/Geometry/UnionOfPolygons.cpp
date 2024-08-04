// Area[i] : area covered by at least i polygon
vector<double> PolyUnion(const vector<vector<Pt>> &P) {
    const int n = P.size();
    vector<double> Area(n + 1);
    vector<Line> vis;
    auto done = [&](Line u) {
        for (auto &v : vis) 
            if (PtSide(u.a, v) == 0 and PtSide(u.b, v) == 0 and sgn((u.a - u.b) * (v.a - v.b)) > 0)
                return true;
        return false;
    };
    auto sweep = [&](Line L, int bel) -> void {
        if (done(L)) return;
        vector<pair<Pt, int>> event;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < P[i].size(); j++) {
                Pt c = P[i][j % P[i].size()];
                Pt d = P[i][(j + 1) % P[i].size()];
                if (sgn((L.a - L.b) ^ (c - d)) != 0) {
                    int s1 = PtSide(c, L) == 1;
                    int s2 = PtSide(d, L) == 1;
                    if (s1 ^ s2) event.emplace_back(LineInter(L, {c, d}), s1 ? 1 : -1);
                } else if (PtSide(c, L) == 0 and sgn((L.a - L.b) * (c - d)) > 0) {
                    event.emplace_back(c, 2);
                    event.emplace_back(d, -2);
                }
            }
        };
        sort(all(event), [&](auto i, auto j) {
            return (L.a - i.ff) * (L.a - L.b) < (L.a - j.ff) * (L.a - L.b);
        });
        int cov = 0, tag = 0;
        Pt lst{0, 0};
        for (auto [p, s] : event) {
            if (cov >= tag) {
                Area[cov] += lst ^ p;
                Area[cov - tag] -= lst ^ p;
            }
            if (abs(s) == 1) cov += s;
            else tag += s / 2;
            lst = p;
        }
        vis.push_back(L);
    };
    for (int i = 0; i < n; i++) for (int j = 0; j < P[i].size(); j++)
        sweep({P[i][j], P[i][(j + 1) % P[i].size()]}, i);
    for (int i = n - 1; i >= 0; i--) Area[i] += Area[i + 1];
    for (int i = 1; i <= n; i++) Area[i] /= 2;
    return Area;
};
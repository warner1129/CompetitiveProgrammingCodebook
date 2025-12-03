// Area[i] : area covered by exactly i polygon
auto PolyWeightUnion(const vector<vector<Pt>> &P, const auto &W) {
    const int n = P.size();
    map<int,double> Area{};
    vector<pair<Line,int>> Ls;
    for (int i = 0; i < n; i++) 
        for (int j = 0, m = P[i].size(); j < m; j++)
            Ls.emplace_back(Line{P[i][j], P[i][(j + 1) % m]}, W[i]);
    auto cmp = [&](auto &l, auto &r) {
        Pt u = l.ft.dir(), v = r.ft.dir();
        if (argcmp(u, v)) return true;
        if (argcmp(v, u)) return false;
        return PtSide(l.ft.a, r.ft) < 0;
    }; /* SPLIT-HASH */
    sort(all(Ls), cmp);
    for (int l = 0, r = 0; l < Ls.size(); l = r) {
        while (r < Ls.size() and !cmp(Ls[l], Ls[r])) r++;
        Line L = Ls[l].ft;
        vector<pair<Pt, pair<int,int>>> event;
        for (auto [R, w] : Ls) {
            if (sgn(L.dir() ^ R.dir()) != 0) {
                int s1 = PtSide(R.a, L) == 1;
                int s2 = PtSide(R.b, L) == 1;
                if (s1 ^ s2) event.emplace_back(LineInter(L, R), pair{ s1 ? w : -w, 0 });
            } else if (PtSide(R.a, L) == 0 and sgn(L.dir() * R.dir()) > 0) {
                event.emplace_back(R.a, pair{ 0, w });
                event.emplace_back(R.b, pair{ 0, -w });
            }
        } /* SPLIT-HASH */
        sort(all(event), [&](auto i, auto j) {
            return (L.a - i.ft) * L.dir() > (L.a - j.ft) * L.dir();
        });
        int cov = 0, tag = 0;
        Pt lst{0, 0};
        for (auto [p, s] : event) {
            if (cov >= tag) {
                auto a = lst ^ p;
                Area[cov] += a;
                Area[cov - tag] -= a;
            }
            cov += s.ft; tag += s.sd;
            lst = p;
        }
    }
    for (auto &[x,y]: Area) y /= 2;
    return Area;
}

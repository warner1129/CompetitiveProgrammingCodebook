// 交集不能為空或無限
vector<Pt> HPI(vector<Line> P) {
    sort(all(P), [&](Line &l, Line &r) {
        return argcmp(l.b - l.a, r.b - r.a);
    });
    int n = P.size(), l = 0, r = 0;
    vector<Pt> it(n);
    vector<Line> se(n);
    se[0] = P[0];
    for (int i = 1; i < n; i++) {
        while (l < r and PtSide(it[r - 1], P[i]) != 1) r--;
        while (l < r and PtSide(it[l], P[i]) != 1) l++;
        se[++r] = P[i];
        if (sgn((se[r].b - se[r].a) ^ (se[r - 1].b - se[r - 1].a)) == 0) {
            r--;
            if (PtSide(P[i].a, se[r]) == 1) se[r] = P[i];
        }
        if (l < r) it[r - 1] = LineInter(se[r - 1], se[r]);
    }
    while (l < r and PtSide(it[r - 1], se[l]) != 1) r--;
    if (r - l <= 1) return {};
    it[r] = LineInter(se[r], se[l]);
    return vector<Pt>(it.begin() + l, it.begin() + r + 1);
}
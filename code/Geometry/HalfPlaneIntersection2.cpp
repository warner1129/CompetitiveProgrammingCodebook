bool cov(Line L, Line P, Line Q) {
    i128 u = (Q.a - P.a) ^ Q.dir();
    i128 v = P.dir() ^ Q.dir();
    i128 x = P.dir().x * u + (P.a - L.a).x * v;
    i128 y = P.dir().y * u + (P.a - L.a).y * v;
    return sgn(x * L.dir().y - y * L.dir().x) * sgn(v) >= 0;
}
bool operator<(Line l, Line m) {
    if (argcmp(l.dir(), m.dir())) return true;
    if (argcmp(m.dir(), l.dir())) return false;
    return PtSide(l.a, m) > 0;
}
vector<Pt> HPI(vector<Line> P) {
    sort(all(P));
    int n = P.size(), l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        if (i and !argcmp(P[i - 1].dir(), P[i].dir())) continue;
        while (l < r and cov(P[i], P[r - 1], P[r])) r--;
        while (l < r and cov(P[i], P[l], P[l + 1])) l++;
        P[++r] = P[i];
    }
    while (l < r and cov(P[l], P[r - 1], P[r])) r--;
    while (l < r and cov(P[r], P[l], P[l + 1])) l++;
    n = r - l + 1;
    if (n <= 2 or !argcmp(P[l].dir(), P[r].dir())) return {};
    vector<Pt> its(n);
    for (int i = 0; i < n; i++)
        its[i] = LineInter(P[i + l], P[(i + 1) % n + l]);
    return its;
}
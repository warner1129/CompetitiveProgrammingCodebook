double SectorArea(Pt a, Pt b, double r) {
    double theta = atan2(a.ss, a.ff) - atan2(b.ss, b.ff);
    while (theta <= 0) theta += 2 * pi;
    while (theta >= 2 * pi) theta -= 2 * pi;
    theta = min(theta, 2 * pi - theta);
    return r * r * theta / 2;
}

vector<Pt> CircleCrossLine(Pt a, Pt b, Pt o, double r) {
    double h = cro(o, a, b) / abs(a - b);
    Pt v = (a - b) / abs(a - b);
    Pt u = Pt{-v.ss, v.ff};
    Pt H = o + u * h;
    h = abs(h);
    vector<Pt> ret;
    if (sig(h - r) <= 0) {
        double d = sqrt(max(0., r * r - h * h));
        for (auto p : {H + (v * d), H - (v * d)})
            if (sig((a - p) * (b - p)) <= 0) {
                ret.push_back(p);
            }
    }
    return ret;
}

double AreaOfCircleTriangle(Pt a, Pt b, double r) {
    if (sig(abs(a) - r) <= 0 and sig(abs(b) - r) <= 0) {
        return abs(a ^ b) / 2;
    }
    if (abs(a) > abs(b)) swap(a, b);
    auto I = CircleCrossLine(a, b, {}, r);
    if (I.size() == 1) return abs(a ^ I[0]) / 2 + SectorArea(I[0], b, r);
    if (I.size() == 2) {
        return SectorArea(a, I[0], r) + SectorArea(I[1], b, r) + abs(I[0] ^ I[1]) / 2;
    }
    return SectorArea(a, b, r);
}
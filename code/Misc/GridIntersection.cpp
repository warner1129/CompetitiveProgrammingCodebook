int det(Pt a, Pt b) { return a.ft * b.sd - a.sd * b.ft; }
// find p s.t (d1 * p, d2 * p) = x
Pt gridInter(Pt d1, Pt d2, Pt x) {
    swap(d1.sd, d2.ft);
    int s = det(d1, d2);
    int a = det(x, d2);
    int b = det(d1, x);
    assert(s != 0);
    if (a % s != 0 or b % s != 0) {
        return //{-1, -1};
    }
    return {a / s, b / s};
}

struct Line {
    Pt a, b;
};
Pt rotate(Pt u) { // pi / 2
    return {-u.ss, u.ff};
}
Pt rotate(Pt u, double a) {
    Pt v{sin(a), cos(a)};
    return {u ^ v, u * v};
} 
Pt unit(Pt x) {
    return x / abs(x);
}
Pt proj(Pt p, Line l) {
    Pt dir = unit(l.b - l.a);
    return l.a + dir * (dir * (p - l.a));
}
int PtSide(Pt p, Line L) {
    return sgn(cro(L.a, L.b, p));
}
bool PtOnSeg(Pt p, Line L) {
    return sgn(cro(L.a, L.b, p)) == 0 and sgn((p - L.a) * (p - L.b)) <= 0;
}
bool isInter(Line l, Line m) {
    if (PtOnSeg(m.a, l) or PtOnSeg(m.b, l) or
        PtOnSeg(l.a, m) or PtOnSeg(l.b, m))
        return true;
    return PtSide(m.a, l) * PtSide(m.b, l) < 0 and
           PtSide(l.a, m) * PtSide(l.b, m) < 0;
}
Pt LineInter(Line l, Line m) {
    double s = cro(m.a, m.b, l.a), t = cro(m.a, m.b, l.b);
    return (l.b * s - l.a * t) / (s - t);
}
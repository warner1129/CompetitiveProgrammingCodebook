struct Line { 
    Pt a, b;
    Pt dir() const { return b - a; }
}; /* SPLIT-HASH */
int PtSide(Pt p, Line L) {
    if constexpr (is_floating_point_v<Real>)
        return sgn(ori(L.a, L.b, p) / abs(L.a - L.b));
    return sgn(ori(L.a, L.b, p)); 
} /* SPLIT-HASH */
bool PtOnSeg(Pt p, Line L) {
    return PtSide(p, L) == 0 and sgn((p - L.a) * (p - L.b)) <= 0;
} /* SPLIT-HASH */
Pt proj(Pt p, Line l) {
    Pt dir = unit(l.b - l.a);
    return l.a + dir * (dir * (p - l.a));
}

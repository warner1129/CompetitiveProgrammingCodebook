using Pt = pair<double, double>;
Pt operator+(Pt a, Pt b) { return {a.ff + b.ff, a.ss + b.ss}; }
Pt operator-(const pdd &a, const pdd &b) { return {a.ff - b.ff, a.ss - b.ss}; }
Pt operator/(const pdd &a, double c) { return {a.ff / c, a.ss / c}; }
Pt operator*(const pdd &a, double c) { return {a.ff * c, a.ss * c}; }
double operator*(pdd &a, pdd &b) { return {a.ff * b.ff + a.ss * b.ss}; }
double abs(pdd x) { return sqrt(x.ff * x.ff + x.ss * x.ss); } 
double cro(Pt a, Pt b, Pt c) { return (b - a) ^ (c - a); }
int sig(double x) { return (x > -eps) - (x < eps); }
Pt Interset(Pt a, Pt b, Pt c, Pt d) {
    long double s = cro(c, d, a), t = -cro(c, d, b);
    return (a * t + b * s) / (s + t);
}
struct Line {
    Pt a{}, b{};
    Line() {}
    Line(Pt _a, Pt _b) : a{_a}, b{_b} {}
};
Pt Interset(Line L, Line R) {
    double s = cro(R.a, R.b, L.a), t = -cro(R.a, R.b, L.b);
    return (L.a * t + L.b * s) / (s + t);
}
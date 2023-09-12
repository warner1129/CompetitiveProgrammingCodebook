using Pt = pair<i64, i64>;
constexpr double eps = 1e-9;
Pt operator+(Pt a, Pt b) { return {a.ff + b.ff, a.ss + b.ss}; }
Pt operator-(Pt a, Pt b) { return {a.ff - b.ff, a.ss - b.ss}; }
Pt operator*(Pt a, double b) { return {a.ff * b, a.ss * b}; }
Pt operator/(Pt a, double b) { return {a.ff / b, a.ss / b}; }
double operator*(Pt a, Pt b) { return a.ff * b.ff + a.ss * b.ss; }
double operator^(Pt a, Pt b) { return a.ff * b.ss - a.ss * b.ff; }
double abs(Pt a) { return sqrt(a * a); }
double cro(Pt a, Pt b, Pt c) { return (b - a) ^ (c - a); }
int sig(double x) { return (x > -eps) - (x < eps); }
Pt Inter(Pt a, Pt b, Pt c, Pt d) {
    double s = cro(c, d, a), t = -cro(c, d, b);
    return (a * t + b * s) / (s + t);
}
struct Line {
    Pt a{}, b{};
    Line() {}
    Line(Pt _a, Pt _b) : a{_a}, b{_b} {}
};
Pt Inter(Line L, Line R) {
    return Inter(L.a, L.b, R.a, R.b);
}
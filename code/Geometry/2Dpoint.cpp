using Pt = pair<double, double>;
using numbers::pi;
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
Pt rot(Pt u, double a) {
    Pt v{sin(a), cos(a)};
    return {u ^ v, u * v};
} 
bool inedge(Pt a, Pt b, Pt c) {
    return ((a - b) ^ (c - b)) == 0 and (a - b) * (c - b) <= 0;
}
bool banana(Pt a, Pt b, Pt c, Pt d) {
    if (inedge(a, c, b) or inedge(a, d, b) or \
        inedge(c, a, d) or inedge(c, b, d))
        return true;
    return sig(cro(a, b, c)) * sig(cro(a, b, d)) < 0 and \
           sig(cro(c, d, a)) * sig(cro(c, d, b)) < 0;
}
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
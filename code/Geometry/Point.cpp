using numbers::pi;
constexpr double eps = 1E-9L;
struct Pt {
    double x{}, y{};
};
Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator*(Pt a, double k) { return {a.x * k, a.y * k}; }
Pt operator/(Pt a, double k) { return {a.x / k, a.y / k}; }
double operator*(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
double operator^(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
auto operator<=>(Pt a, Pt b) { return (a.x != b.x) ? a.x <=> b.x : a.y <=> b.y; }
int sgn(double x) { return (x > -eps) - (x < eps); }
double abs(Pt a) { return sqrt(a * a); }
double abs2(Pt a) { return a * a; }
double ori(Pt a, Pt b, Pt c) { return (b - a) ^ (c - a); }
double arg(Pt x) { return atan2(x.y, x.x); }
bool argcmp(const Pt &a, const Pt &b) {
    bool f = Pt{a.y, a.x} < Pt{};
    bool g = Pt{b.y, b.x} < Pt{};
    return f == g ? (a ^ b) > 0 : f < g;
}
Pt unit(Pt x) { return x / abs(x); }
Pt rotate(Pt u) { // pi / 2
    return {-u.y, u.x};
}
Pt rotate(Pt u, double a) {
    Pt v{sin(a), cos(a)};
    return {u ^ v, u * v};
}
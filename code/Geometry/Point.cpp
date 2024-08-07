using numbers::pi;
struct Pt {
    double x{}, y{};
    Pt operator+(const Pt &o) const { return {x + o.x, y + o.y}; }
    Pt operator-(const Pt &o) const { return {x - o.x, y - o.y}; }
    Pt operator*(double k) const { return {x * k, y * k}; }
    Pt operator/(double k) const { return {x / k, y / k}; }
    double operator*(const Pt &o) const { return x * o.x + y * o.y; }
    double operator^(const Pt &o) const { return x * o.y - y * o.x; }
    auto operator<=>(const Pt &o) const { return (x != o.x) ? x <=> o.x : y <=> o.y; }
    bool operator==(const Pt &o) const { return x == o.x and y == o.y; }
};
constexpr double eps = 1E-9L;
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
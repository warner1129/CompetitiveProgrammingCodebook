using numbers::pi;
template<class T> inline constexpr T eps = numeric_limits<T>::epsilon() * 1E6;
template<class T>
struct Point { using Pt = Point;
    T x{}, y{};
    Pt operator+(Pt a) { return {x + a.x, y + a.y}; }
    Pt operator-(Pt a) { return {x - a.x, y - a.y}; }
    Pt operator*(T k) { return {x * k, y * k}; }
    Pt operator/(T k) { return {x / k, y / k}; }
    T operator*(Pt a) { return x * a.x + y * a.y; }
    T operator^(Pt a) { return x * a.y - y * a.x; }
    auto operator<=>(const Pt&) const = default;
    bool operator==(const Pt&) const = default;
    Pt operator-() const { return {-x, -y}; }
};
using Real = long double;
using Pt = Point<Real>;
int sgn(Real x) { return (x > -eps<Real>)- (x < eps<Real>); }
Real ori(Pt a, Pt b, Pt c) { return (b - a) ^ (c - a); }
Pt norm(Pt u) { return {-u.y, u.x}; } /* SPLIT-HASH */
bool argcmp(const Pt &a, const Pt &b) { // arg(a) < arg(b)
    int f = (-norm(a) > Pt{} ? 1 : -1) * (a != Pt{});
    int g = (-norm(b) > Pt{} ? 1 : -1) * (b != Pt{});
    return f == g ? (a ^ b) > 0 : f < g;
} /* SPLIT-HASH */
Real abs2(Pt a) { return a * a; }
// floating point only /* SPLIT-HASH */
Pt rotate(Pt u, Real a) {
    Pt v{sinl(a), cosl(a)};
    return {u ^ v, u * v};
} /* SPLIT-HASH */
Real abs(Pt a) { return sqrtl(a * a); }
Real arg(Pt x) { return atan2l(x.y, x.x); }
Pt unit(Pt x) { return x / abs(x); }
struct Line { 
    Pt a, b;
    Pt dir() const { return b - a; }
}; /* SPLIT-HASH */
int PtSide(Pt p, Line L) {
    return sgn(ori(L.a, L.b, p)); // for int
    return sgn(ori(L.a, L.b, p) / abs(L.a - L.b));
} /* SPLIT-HASH */
bool PtOnSeg(Pt p, Line L) {
    return PtSide(p, L) == 0 and sgn((p - L.a) * (p - L.b)) <= 0;
} /* SPLIT-HASH */
Pt proj(Pt p, Line l) {
    Pt dir = unit(l.b - l.a);
    return l.a + dir * (dir * (p - l.a));
} /* SPLIT-HASH */
Pt proj(Pt p, Line l) {
    auto d = l.b - l.a, w = p - l.a;
    return l.a + d * (w * d / abs2(d));
} /* SPLIT-HASH */
Pt reflect(Pt p, Line l) {
    auto d = l.b - l.a, w = p - l.a;
    return p + norm(d) * (w ^ d / abs2(d) * 2);
} /* SPLIT-HASH */
Pt linearTransformation(Line p, Line q, Pt r) {
    Pt dp = p.b - p.a, dq = q.b - q.a, n{ dp ^ dq, dp * dq };
    Pt w = r - p.a; return q.a + Pt{ w ^ n, w * n } / abs2(dp);
} // p, r ~ q, ans /* SPLIT-HASH */
struct Cir { Pt o; Real r;  };
bool disjunct(const Cir &a, const Cir &b) {
    return sgn(abs(a.o - b.o) - a.r - b.r) >= 0; 
}
bool contain(const Cir &a, const Cir &b) {
    return sgn(a.r - b.r - abs(a.o - b.o)) >= 0; 
}

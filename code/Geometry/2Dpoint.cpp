using Pt = pair<double, double>;
using numbers::pi;

constexpr double eps = 1E-9L;

Pt operator+(Pt a, Pt b) { return {a.ff + b.ff, a.ss + b.ss}; }
Pt operator-(Pt a, Pt b) { return {a.ff - b.ff, a.ss - b.ss}; }
Pt operator*(Pt a, double b) { return {a.ff * b, a.ss * b}; }
Pt operator/(Pt a, double b) { return {a.ff / b, a.ss / b}; }
double operator*(Pt a, Pt b) { return a.ff * b.ff + a.ss * b.ss; }
double operator^(Pt a, Pt b) { return a.ff * b.ss - a.ss * b.ff; }

double abs(Pt a) { return sqrt(a * a); }
double cro(Pt a, Pt b, Pt c) { return (b - a) ^ (c - a); }
int sgn(double x) { return (x > -eps) - (x < eps); }
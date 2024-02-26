// Binary search on Stern-Brocot Tree
// Parameters: n, pred
//  n: Q_n is the set of all rational numbers whose denominator does not exceed n
//  pred: pair<i64, i64> -> bool, pred({0, 1}) must be true
// Return value: {{a, b}, {x, y}}
//  a/b is bigger value in Q_n that satisfy pred()
//  x/y is smaller value in Q_n that not satisfy pred()
// Complexity: O(log^2 n)
using Pt = pair<i64, i64>;
Pt operator+(Pt a, Pt b) { return {a.ff + b.ff, a.ss + b.ss}; }
Pt operator*(i64 a, Pt b) { return {a * b.ff, a * b.ss}; }
pair<pair<i64, i64>, pair<i64, i64>> FractionSearch(i64 n, const auto &pred) {
    pair<i64, i64> low{0, 1}, hei{1, 0};
    while (low.ss + hei.ss <= n) {
        bool cur = pred(low + hei);
        auto &fr{cur ? low : hei}, &to{cur ? hei : low};
        u64 L = 1, R = 2;
        while ((fr + R * to).ss <= n and pred(fr + R * to) == cur) {
            L *= 2;
            R *= 2;
        }
        while (L + 1 < R) {
            u64 M = (L + R) / 2;
            ((fr + M * to).ss <= n and pred(fr + M * to) == cur ? L : R) = M;
        }
        fr = fr + L * to;
    }
    return {low, hei};
}
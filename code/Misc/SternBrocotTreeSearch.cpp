// Binary search on Stern-Brocot Tree
// Parameters:
// n: Q_n is the set of all rational numbers whose denominator does not exceed n
// pred: pair<i64, i64> -> bool, pred({0, 1}) must be true
// Return value:
// L: {p, q} p/q is last value in Q_n that satisfy pred()
// R: {p, q} p/q is first value in Q_n that not satisfy pred() or inf
// Complexity: O(log^2 n)
pair<pair<i64, i64>, pair<i64, i64>> SternBrocotTreeSearch(i64 n, const auto &pred) {
    auto Merge = [&](pair<i64, i64> a, pair<i64, i64> b, i64 p) -> pair<i64, i64> {
        if (p == 0) return {a.ff + b.ff, a.ss + b.ss};
        if (p < 0) p = -p, swap(a, b);
        return {a.ff + b.ff * p, a.ss + b.ss * p};
    };
    pair<i64, i64> L{0, 1}, R{1, 0};
    while (L.ss + R.ss <= n) {
        i64 dn = (n - R.ss) / L.ss;
        i64 up = R.ss == 0 ? inf<i64> : (n - L.ss) / R.ss + 1;
        i64 pos = *ranges::partition_point(views::iota(-dn, up),
                [&](i64 p) { return pred(Merge(L, R, p)); });
        auto nL = Merge(L, R, pos - 1);
        auto nR = (pos == up) ? R : Merge(L, R, pos);
        L = nL;
        R = nR;
    }
    return {L, R};
}
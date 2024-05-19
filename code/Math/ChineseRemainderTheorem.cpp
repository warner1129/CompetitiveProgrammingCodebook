// O(NlogC)
// E = {(m, r), ...}: x mod m_i = r_i
// return {M, R} x mod M = R
// return {-1, -1} if no solution
pair<i64, i64> CRT(vector<pair<i64, i64>> E) {
    i128 R = 0, M = 1;
    for (auto [m, r] : E) {
        i64 g, x, y, d;
        g = exgcd(M, m, x, y);
        d = r - R;
        if (d % g != 0) {
            return {-1, -1};
        }
        R += d / g * M * x;
        M = M * m / g;
        R = (R % M + M) % M;
    }
    return {M, R};
}
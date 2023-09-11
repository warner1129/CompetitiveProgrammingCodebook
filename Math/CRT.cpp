pair<i64, i64> exgcd(i64 a, i64 b) { // ax + by = 1
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a % b);
    return {y, x - a / b * y};
};

i64 CRT(vector<pair<i64, i64>> E) {
    i128 R = 0, M = 1;
    for (auto [r, m] : E) {
        i128 d = r - R, g = gcd<i64>(M, m);
        if (d % g != 0) return -1;
        i128 x = exgcd(M / g, m / g).ff * d / g;
        R += M * x;
        M = M * m / g;
        R = (R % M + M) % M;
    }
    return R;
}

int SqrtMod(int n, int P) { // 0 <= x < P
    if (P == 2 or n == 0) return n;
    if (pow(n, (P - 1) / 2, P) != 1) return -1;
    mt19937 rng(12312);
    i64 z = 0, w;
    while (pow(w = (z * z - n + P) % P, (P - 1) / 2, P) != P - 1)
        z = rng() % P;
    const auto M = [P, w](auto &u, auto &v) {
        return make_pair(
            (u.ff * v.ff + u.ss * v.ss % P * w) % P,
            (u.ff * v.ss + u.ss * v.ff) % P
        );
    };
    pair<i64, i64> r(1, 0), e(z, 1);
    for (int w = (P + 1) / 2; w; w >>= 1, e = M(e, e))
        if (w & 1) r = M(r, e);
    return r.ff; // sqrt(n) mod P where P is prime
}
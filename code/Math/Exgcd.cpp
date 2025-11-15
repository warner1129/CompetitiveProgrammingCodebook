i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) return x = 1, y = 0, a;
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
} // ax + by = gcd(a, b) /* SPLIT-HASH */
i64 inverse(i64 a, i64 b, i64 m) {
    auto g = gcd(m, a);
    if (b % g) return -1;
    i64 x, y; exgcd(a/g, m/g, x, y);
    auto r = x * (b/g) % m;
    if (r < 0) r += m;
    return r % (m/g);
} // ar ≡ b % m

u64 mul(u64 a, u64 b, u64 M) {
    i64 r = a * b - M * u64(1.L / M * a * b);
    return r + M * ((r < 0) - (r >= (i64)M));
}
u64 power(u64 a, u64 b, u64 M) {
    u64 r = 1;
    for (; b; b /= 2, a = mul(a, a, M))
        if (b & 1) r = mul(r, a, M);
    return r;
} /* SPLIT-HASH */
bool isPrime(u64 n) {
    if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
    auto magic = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    u64 s = __builtin_ctzll(n - 1), d = n >> s;
    for (u64 x : magic) {
        u64 p = power(x % n, d, n), i = s;
        while (p != 1 and p != n - 1 and x % n && i--)
            p = mul(p, p, n);
        if (p != n - 1 and i != s) return 0;
    }
    return 1;
} /* SPLIT-HASH */
u64 pollard(u64 n) {
    u64 c = 1;
    auto f = [&](u64 x) { return mul(x, x, n) + c; };
    u64 x = 0, y = 0, p = 2, q, t = 0;
    while (t++ % 128 or gcd(p, n) == 1) {
        if (x == y) c++, y = f(x = 2);
        if (q = mul(p, x > y ? x - y : y - x, n)) p = q;
        x = f(x); y = f(f(y));
    }
    return gcd(p, n);
} /* SPLIT-HASH */
u64 primeFactor(u64 n) {
    return isPrime(n) ? n : primeFactor(pollard(n));
}

// comb(n, m) % M, M = p^k
// O(M)-O(log(n))
struct Lucas {
    const i64 p, M;
    vector<i64> f;
    Lucas(int p, int M) : p(p), M(M), f(M + 1) {
        f[0] = 1;
        for (int i = 1; i <= M; i++) {
            f[i] = f[i - 1] * (i % p == 0 ? 1 : i) % M;
        }
    }
    i64 CountFact(i64 n) {
        i64 c = 0;
        while (n) c += (n /= p);
        return c;
    }
    // (n! without factor p) % p^k
    i64 ModFact(i64 n) {
        i64 r = 1;
        while (n) {
            r = r * power(f[M], n / M % 2, M) % M * f[n % M] % M;
            n /= p;
        }
        return r;
    }
    i64 ModComb(i64 n, i64 m) {
        if (m < 0 or n < m) return 0;
        i64 c = CountFact(n) - CountFact(m) - CountFact(n - m);
        i64 r = ModFact(n) * power(ModFact(m), M / p * (p - 1) - 1, M) % M
                           * power(ModFact(n - m), M / p * (p - 1) - 1, M) % M;
        return r * power(p, c, M) % M;
    }
};

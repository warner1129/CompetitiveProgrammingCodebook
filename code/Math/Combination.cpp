template <size_t N>
struct Comb {
    array<i64, N + 1> fac, ifac, inv;
    Comb() : fac{1, 1}, ifac{1, 1}, inv{0, 1} {
        for (int i = 2; i <= N; i++) {
            inv[i] = inv[mod % i] * (mod - mod / i) % mod;
            fac[i] = fac[i - 1] * i % mod;
            ifac[i] = ifac[i - 1] * inv[i] % mod;
        }
    }
    i64 operator()(int n) {
        return n < 0 ? ifac[-n] : fac[n];
    }
    i64 operator()(int n, int m) {
        if (n < m or m < 0) return 0;
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
};
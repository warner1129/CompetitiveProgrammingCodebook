template<size_t N>
struct Comb {
    array<int, N + 1> fac, ifac, inv;
    Comb() : fac{1, 1}, ifac{1, 1}, inv{0, 1} {
        for (int i = 2; i <= N; i++) {
            inv[i] = mul(inv[mod % i], mod - mod / i);
            fac[i] = mul(fac[i - 1], i);
            ifac[i] = mul(ifac[i - 1], inv[i]);
        }
    }
    int operator()(int n) {
        return n < 0 ? ifac[-n] : fac[n];
    }
    int operator()(int n, int m) {
        return mul(fac[n], ifac[m], ifac[n - m]);
    }
};

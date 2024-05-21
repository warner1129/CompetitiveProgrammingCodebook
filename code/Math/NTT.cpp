template<i64 M, i64 root>
struct NTT {
    array<i64, 21> e{}, ie{};
    NTT() {
        e[20] = power(root, (M - 1) >> 20, M);
        ie[20] = power(e[20], M - 2, M);
        for (int i = 19; i >= 0; i--) {
            e[i] = e[i + 1] * e[i + 1] % M;
            ie[i] = ie[i + 1] * ie[i + 1] % M;
        }
    }
    void operator()(vector<i64> &v, bool inv) {
        int n = v.size();
        for (int i = 0, j = 0; i < n; i++) {
            if (i < j) swap(v[i], v[j]);
            for (int k = n / 2; (j ^= k) < k; k /= 2);
        }
        for (int m = 1; m < n; m *= 2) {
            i64 w = (inv ? ie : e)[__lg(m) + 1];
            for (int i = 0; i < n; i += m * 2) {
                i64 cur = 1;
                for (int j = i; j < i + m; j++) {
                    i64 g = v[j], t = cur * v[j + m] % M;
                    v[j] = (g + t) % M;
                    v[j + m] = (g - t + M) % M;
                    cur = cur * w % M;
                }
            }
        }
        if (inv) {
            i64 in = power(n, M - 2, M);
            for (int i = 0; i < n; i++) v[i] = v[i] * in % M;
        }
    }
};
NTT<mod, 3> ntt;
vector<i64> operator*(vector<i64> f, vector<i64> g) {
    int n = ssize(f) + ssize(g) - 1;
    int len = bit_ceil(1ull * n);
    f.resize(len);
    g.resize(len);
    ntt(f, 0), ntt(g, 0);
    for (int i = 0; i < len; i++) {
        (f[i] *= g[i]) %= mod;
    }
    ntt(f, 1);
    f.resize(n);
    return f;
}
vector<i64> convolution_ll(const vector<i64> &f, const vector<i64> &g) {
    constexpr i64 M1 = 998244353, G1 = 3;
    constexpr i64 M2 = 985661441, G2 = 3;
    constexpr i64 M1M2 = M1 * M2;
    constexpr i64 M1m1 = M2 * power(M2, M1 - 2, M1);
    constexpr i64 M2m2 = M1 * power(M1, M2 - 2, M2);
    auto c1 = convolution<M1, G1>(f, g);
    auto c2 = convolution<M2, G2>(f, g);
    for (int i = 0; i < c1.size(); i++) {
        c1[i] = ((i128)c1[i] * M1m1 + (i128)c2[i] * M2m2) % M1M2;
    }
    return c1;
}
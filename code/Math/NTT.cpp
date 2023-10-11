constexpr i64 cpow(i64 a, i64 b, i64 m) {
    i64 ret = 1;
    for (; b; b >>= 1, a = a * a % m)
        if (b & 1) ret = ret * a % m;
    return ret;
};
template<i64 M, i64 G>
struct NTT {
    static constexpr i64 iG = cpow(G, M - 2, M);
    void operator()(vector<i64> &v, bool inv) {
        int n = v.size();
        for (int i = 0, j = 0; i < n; i++) {
            if (i < j) swap(v[i], v[j]);
            for (int k = n / 2; (j ^= k) < k; k /= 2);
        }
        for (int mid = 1; mid < n; mid *= 2) {
            i64 w = cpow((inv ? iG : G), (M - 1) / (mid + mid), M);
            for (int i = 0; i < n; i += mid * 2) {
                i64 now = 1;
                for (int j = i; j < i + mid; j++, now = now * w % M) {
                    i64 x = v[j], y = v[j + mid];
                    v[j] = (x + y * now) % M;
                    v[j + mid] = (x - y * now) % M;
                }
            }
        }
        if (inv) {
            i64 in = cpow(n, M - 2, M);
            for (int i = 0; i < n; i++) v[i] = v[i] * in % M;
        }
    }
};
template<i64 M, i64 G>
vector<i64> convolution(vector<i64> f, vector<i64> g) {
    NTT<M, G> ntt;
    int sum = f.size() + g.size() - 1;
    int len = bit_ceil((u64)sum);
    f.resize(len); g.resize(len);
    ntt(f, 0), ntt(g, 0);
    for (int i = 0; i < len; i++) (f[i] *= g[i]) %= M;
    ntt(f, 1);	
    f.resize(sum);
    for (int i = 0; i < sum; i++) if (f[i] < 0) f[i] += M;
    return f;
}
vector<i64> convolution_ll(const vector<i64> &f, const vector<i64> &g) {
    constexpr i64 M1 = 998244353, G1 = 3;
    constexpr i64 M2 = 985661441, G2 = 3;
    constexpr i64 M1M2 = M1 * M2;
    constexpr i64 M1m1 = M2 * cpow(M2, M1 - 2, M1);
    constexpr i64 M2m2 = M1 * cpow(M1, M2 - 2, M2);
    auto c1 = convolution<M1, G1>(f, g);
    auto c2 = convolution<M2, G2>(f, g);
    for (int i = 0; i < c1.size(); i++) {
        c1[i] = ((i128)c1[i] * M1m1 + (i128)c2[i] * M2m2) % M1M2;
    }
    return c1;
}
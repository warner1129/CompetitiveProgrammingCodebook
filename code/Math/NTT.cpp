template<i64 M, i64 root>
struct NTT {
	static const int Log = 21;
    array<i64, Log + 1> e{}, ie{};
    NTT() {
		static_assert(__builtin_ctz(M - 1) >= Log);
        e[Log] = power(root, (M - 1) >> Log, M);
        ie[Log] = power(e[Log], M - 2, M);
        for (int i = Log - 1; i >= 0; i--) {
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
}; /* SPLIT-HASH */
template<int M, int G>
vector<i64> convolution(vector<i64> f, vector<i64> g) {
	static NTT<M, G> ntt;
    int n = ssize(f) + ssize(g) - 1;
    int len = bit_ceil(1ull * n);
    f.resize(len);
    g.resize(len);
    ntt(f, 0), ntt(g, 0);
    for (int i = 0; i < len; i++) {
        (f[i] *= g[i]) %= M;
    }
    ntt(f, 1);
    f.resize(n);
    return f;
} /* SPLIT-HASH */
vector<i64> inv(vector<i64> f) {
    const int n = f.size();
    int k = 1;
    vector<i64> g{inv(f[0])}, t;
    for (i64 &x : f) {
        x = (mod - x) % mod;
    }
    t.reserve(n);
    while (k < n) {
        k = min(k * 2, n);
        g.resize(k);
        t.assign(f.begin(), f.begin() + k);
        auto h = g * t;
        h.resize(k);
        (h[0] += 2) %= mod;
        g = g * h;
        g.resize(k);
    }
    g.resize(n);
    return g;
} /* SPLIT-HASH */
// CRT
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
// 2D convolution
vector<vector<i64>> operator*(vector<vector<i64>> f, vector<vector<i64>> g) {
    const int n = f.size() + g.size() - 1;
    const int m = f[0].size() + g[0].size() - 1;
    int len = bit_ceil(1ull * max(n, m));
    f.resize(len);
    g.resize(len);
    for (auto &v : f) {
        v.resize(len);
        ntt(v, 0);
    }
    for (auto &v : g) {
        v.resize(len);
        ntt(v, 0);
    }
    for (int i = 0; i < len; i++)
        for (int j = 0; j < i; j++) {
            swap(f[i][j], f[j][i]);
            swap(g[i][j], g[j][i]);
        }
    for (int i = 0; i < len; i++) {
        ntt(f[i], 0);
        ntt(g[i], 0);
    }
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++) {
            f[i][j] = mul(f[i][j], g[i][j]);
        }
    for (int i = 0; i < len; i++) {
        ntt(f[i], 1);
    }
    for (int i = 0; i < len; i++)
        for (int j = 0; j < i; j++) {
            swap(f[i][j], f[j][i]);
        }
    for (auto &v : f) {
        ntt(v, 1);
        v.resize(m);
    }
    f.resize(n);
    return f;
}

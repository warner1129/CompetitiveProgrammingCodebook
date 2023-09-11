// 17 -> 3
// 97 -> 5
// 193 -> 5
// 998244353 -> 3
// 985661441 -> 3

i64 power(i64 a, i64 b, i64 M) {
    i64 ret = 1;
    for (; b; b >>= 1, a = a * a % M)
        if (b & 1) ret = ret * a % M;
    return ret;
};

template<i64 mod, i64 G>
vector<i64> convolution(vector<i64> f, vector<i64> g) {
    const i64 iG = power(G, mod - 2, mod);

    auto NTT = [&](vector<i64> &v, bool inv) {
        int n = v.size();
        for (int i = 0, j = 0; i < n; i++) {
            if (i < j) swap(v[i], v[j]);
            for (int k = n / 2; (j ^= k) < k; k /= 2);
        }
        for (int mid = 1; mid < n; mid *= 2) {
            i64 w = power((inv ? iG : G), (mod - 1) / (mid + mid), mod);
            for (int i = 0; i < n; i += mid * 2) {
                i64 now = 1;
                for (int j = i; j < i + mid; j++, now = now * w % mod) {
                    i64 x = v[j], y = v[j + mid];
                    v[j] = (x + y * now) % mod;
                    v[j + mid] = (x - y * now) % mod;
                }
            }
        }
        if (inv) {
            i64 in = power(n, mod - 2, mod);
            for (int i = 0; i < n; i++) v[i] = v[i] * in % mod;
        }
    };

    int sum = f.size() + g.size() - 1, len = 1;
    while (len < sum) len <<= 1;
    f.resize(len); g.resize(len);
    NTT(f, 0), NTT(g, 0);
    for (int i = 0; i < len; i++) (f[i] *= g[i]) %= mod;
    NTT(f, 1);	
    f.resize(sum);
    for (int i = 0; i < sum; i++) if (f[i] < 0) f[i] += mod;

    return f;
}

vector<i64> mul(const vector<i64> &f, const vector<i64> &g) {
    constexpr int M1 = 998244353, G1 = 3;
    constexpr int M2 = 985661441, G2 = 3;
    const __int128_t M1M2 = (__int128_t)M1 * M2;
    const __int128_t M1m1 = (__int128_t)M2 * power(M2, M1 - 2, M1);
    const __int128_t M2m2 = (__int128_t)M1 * power(M1, M2 - 2, M2);
    
    auto p = convolution<M1, G1>(f, g);
    auto q = convolution<M2, G2>(f, g);
    auto cal = [&](i64 a, i64 b) -> i64 { return (a * M1m1 + b * M2m2) % M1M2; };
    for (int i = 0; i < p.size(); i++) p[i] = cal(p[i], q[i]);
    return p;
}

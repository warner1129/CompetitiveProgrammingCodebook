constexpr i64 M = (1LL << 61) - 1;
constexpr i64 mul(i64 a, i64 b) {
    return (i128)a * b % M;
}
constexpr i64 power(i64 a, i64 b) {
    i64 r = 1;
    for (; b; b >>= 1, a = mul(a, a))
        if (b & 1) r = mul(r, a);
    return r;
}
constexpr i64 P = 1e9 + 321;
constexpr i64 iP = power(P, M - 2);
vector<i64> pw{1}, ipw{1};
void extend(size_t s) {
    while (pw.size() < s + 1) {
        pw.push_back(mul(pw.back(), P));
        ipw.push_back(mul(ipw.back(), iP));
    }
}
struct Hash {
    vector<i64> suf;
    Hash(string_view s) {
        int n = s.size();
        suf.assign(n + 1, 0);
        extend(n);
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = (mul(s[i], pw[i]) + suf[i + 1]) % M;
        }
    }
    pair<i64, int> operator()(int l, int r) {
        return {mul((suf[l] - suf[r] + M), ipw[l]), r - l};
    }
};
pair<i64, int> combine(pair<i64, int> a, pair<i64, int> b) {
    return {(a.ff + mul(b.ff, pw[a.ss])) % M, a.ss + b.ss};
}

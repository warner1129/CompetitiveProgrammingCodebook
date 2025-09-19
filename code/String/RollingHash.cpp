struct RollingHash {
    static constexpr u64 mod = (1LL << 61) - 1, base = 1E9 + 7;
    u64 mul(u128 a, u128 b) { return a * b % mod; }
    const int n;
    vector<u64> suf, pw;
    RollingHash(string_view s) : n(s.size()) {
        suf.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = (mul(suf[i + 1], base) + hash<int>{}(s[i])) % mod;
            pw[n - i] = mul(pw[n - i - 1], base);
        }
    }
    u64 seg_hash(int l, int r) {
        return (suf[l] + mod - mul(suf[r], pw[r - l])) % mod;
    }
    int lcp(int a, int b) {
        int len = n - max(a, b);
        return *ranges::partition_point(views::iota(0, len + 1), [&](int l) {
            return seg_hash(a, a + l) == seg_hash(b, b + l);
        }) - 1;
    }
    int lcs(int a, int b) {
        a++, b++;
        int len = min(a, b);
        return *ranges::partition_point(views::iota(0, len + 1), [&](int l) {
            return seg_hash(a - l, a) == seg_hash(b - l, b);
        }) - 1;
    }
};

// C(N, M) mod D
i64 Lucas(i64 N, i64 M, i64 D) { 
    auto Factor = [&](i64 x) -> vector<pair<i64, i64>> {
        vector<pair<i64, i64>> r;
        for (i64 i = 2; x > 1; i++)
            if (x % i == 0) {
                i64 c = 0;
                while (x % i == 0) x /= i, c++;
                r.emplace_back(i, c);
            }
        return r;
    };
    auto Pow = [&](i64 a, i64 b, i64 m) -> i64 {
        i64 r = 1;
        for (; b; b >>= 1, a = a * a % m)
            if (b & 1) r = r * a % m;
        return r;
    };
    vector<pair<i64, i64>> E;
    for (auto [p, q] : Factor(D)) {
        const i64 mod = Pow(p, q, 1 << 30);
        auto CountFact = [&](i64 x) -> i64 {
            i64 c = 0;
            while (x) c += (x /= p);
            return c;
        };
        auto CountBino = [&](i64 x, i64 y) { return CountFact(x) - CountFact(y) - CountFact(x - y); };
        auto Inv = [&](i64 x) -> i64 { return (exgcd(x, mod).ff % mod + mod) % mod; };
        vector<i64> pre(mod + 1);
        pre[0] = pre[1] = 1;
        for (i64 i = 2; i <= mod; i++) pre[i] = (i % p == 0 ? 1 : i) * pre[i - 1] % mod;
        function<i64(i64)> FactMod = [&](i64 n) -> i64 {
            if (n == 0) return 1;
            return FactMod(n / p) * Pow(pre[mod], n / mod, mod) % mod * pre[n % mod] % mod;
        };
        auto BinoMod = [&](i64 x, i64 y) -> i64 {
            return FactMod(x) * Inv(FactMod(y)) % mod * Inv(FactMod(x - y)) % mod;
        };
        i64 r = BinoMod(N, M) * Pow(p, CountBino(N, M), mod) % mod;
        E.emplace_back(r, mod);
    };
    return CRT(E);
}

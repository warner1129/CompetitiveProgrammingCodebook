dp[61][0][0][0][7] = 1;
for (int h = 60; h >= 0; h--) {
    int s = (n >> h & 1) * 7;
    for (int x = 0; x < 8; x++) if (__builtin_parity(x) == 0) {
        for (int y = 0; y < 8; y++)
            if (((y & ~s) & x) == 0) {
                for (int a = 0; a < A[0]; a++)
                    for (int b = 0; b < A[1]; b++)
                        for (int c = 0; c < A[2]; c++) {
                            if (dp[h + 1][a][b][c][y] == 0) continue;
                            i64 i = ((x >> 2 & 1LL) << h) % A[0];
                            i64 j = ((x >> 1 & 1LL) << h) % A[1];
                            i64 k = ((x >> 0 & 1LL) << h) % A[2];
                            auto &val = 
                            dp[h][(i + a) % A[0]][(j + b) % A[1]][(k + c) % A[2]][y & ~(s ^ x)];
                            val = add(val, dp[h + 1][a][b][c][y]);
                        }
            }
    }
}
pair<i64, i64> Split(i64 x) {
    if (x == 1) return {0, 0}; 
    i64 h = __lg(x);
    i64 fill = (1LL << (h + 1)) - 1;
    i64 l = (1LL << h) - 1 - max(0LL, fill - x - (1LL << (h - 1)));
    i64 r = x - 1 - l;
    return {l, r};
};
{
    auto [ls, l] = DP(lo);
    auto [rs, r] = DP(hi);
    if (r < K) {
        cout << "Impossible\n";
        return;
    }
    if (l == K) cout << ls << '\n';
    else if (r == K) cout << rs << '\n';
    else {
        cout << (ls * (r - K) + rs * (K - l)) / (r - l) << '\n';
    }
}
{
    auto F = [&](int L, int R) -> i64 {
        static vector<int> cnt(n);
        static int l = 0, r = -1;
        static i64 ans = 0;
 
        auto Add = [&](int x) {
            ans += cnt[A[x]]++;
        };
        auto Del = [&](int x) {
            ans -= --cnt[A[x]];
        };
        
        while (r < R) Add(++r);
        while (L < l) Add(--l);
        while (R < r) Del(r--);
        while (l < L) Del(l++);
        
        return ans;
    };
 
    vector<i64> dp(n), tmp(n);
    function<void(int, int, int, int)> sol = [&](int l, int r, int x, int y) {
        if (l > r) return;
        int mid = (l + r) / 2;
        int z = mid;
        for (int i = min(y, mid - 1); i >= x; i--)
            if (chmin(tmp[mid], dp[i] + F(i + 1, mid))) {
                z = i;
            }
        if (l == r) return;
        sol(l, mid - 1, x, z);
        sol(mid + 1, r, z, y);
    };
 
    for (int i = 0; i < n; i++)
        dp[i] = F(0, i);
 
    for (int i = 2; i <= m; i++) {
        tmp.assign(n, inf<i64>);
        sol(0, n - 1, 0, n - 1);
        dp = tmp;
    }
 
    cout << dp[n - 1] << '\n';
}
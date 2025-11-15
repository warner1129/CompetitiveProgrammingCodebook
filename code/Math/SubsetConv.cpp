vector<i64> SubsetConv(vector<i64> f, vector<i64> g) {
    const int n = f.size();
    const int U = __lg(n) + 1;
    vector F(U, vector<i64>(n));
    auto G = F, H = F;
    for (u64 i = 0; i < n; i++) {
        F[popcount(i)][i] = f[i];
        G[popcount(i)][i] = g[i];
    }
    for (int i = 0; i < U; i++) {
        FWT(F[i], ORop);
        FWT(G[i], ORop);
    } /* SPLIT-HASH */
    for (int i = 0; i < U; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k < n; k++)
                H[i][k] = (H[i][k] + F[i - j][k] * G[j][k]) % mod;
    for (int i = 0; i < U; i++) FWT(H[i], ORinv);
    for (u64 i = 0; i < n; i++) f[i] = H[popcount(i)][i];
    return f;
}

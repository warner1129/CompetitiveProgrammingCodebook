vector<i64> SubsetConv(vector<i64> f, vector<i64> g) {
    const int n = f.size();
    const int U = __lg(n) + 1;
    vector F(U, vector<i64>(n));
    auto G = F, H = F;
    for (int i = 0; i < n; i++) {
        F[popcount<u64>(i)][i] = f[i];
        G[popcount<u64>(i)][i] = g[i];
    }
    for (int i = 0; i < U; i++) {
        FWT(F[i], ORop);
        FWT(G[i], ORop);
    }
    for (int i = 0; i < U; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k < n; k++)
                H[i][k] = (H[i][k] + F[i - j][k] * G[j][k]) % mod;
    for (int i = 0; i < U; i++) FWT(H[i], ORinv);
    for (int i = 0; i < n; i++) f[i] = H[popcount<u64>(i)][i];
    return f;
}
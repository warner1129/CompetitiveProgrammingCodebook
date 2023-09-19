void FWT(vector<int> &f, int l, int r, auto &op) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    FWT(f, l, m, op), FWT(f, m, r, op);
    for (int i = l, j = m; i < m; i++, j++)
        op(f[i], f[j]);
}

void iFWT(vector<int> &f, int l, int r, auto &op) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    for (int i = l, j = m; i < m; i++, j++)
        op(f[i], f[j]);
    iFWT(f, l, m, op), iFWT(f, m, r, op);
}

vector<int> BitConv(int n, vector<int> f, vector<int> g, const auto &op, const auto &iop) {
    const int N = 1 << n;
    FWT(f, 0, N, op);
    FWT(g, 0, N, op);
    for (int i = 0; i < N; i++)
        f[i] = mul(f[i], g[i]);
    iFWT(f, 0, N, iop);
    return f;
}
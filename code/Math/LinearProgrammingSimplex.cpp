// max{cx} subject to {Ax<=b, x>=0}
// n: constraints, m: vars !!!
// x[] is the optimal solution vector
// usage : 
// x = simplex(A, b, c); (A <= 100 x 100)
vector<double> simplex(
        const vector<vector<double>> &a,
        const vector<double> &b, 
        const vector<double> &c) {
    
    int n = (int)a.size(), m = (int)a[0].size() + 1;
    vector val(n + 2, vector<double>(m + 1));
    vector<int> idx(n + m);
    iota(all(idx), 0);
    int r = n, s = m - 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j)
            val[i][j] = -a[i][j];
        val[i][m - 1] = 1;
        val[i][m] = b[i];
        if (val[r][m] > val[i][m])
            r = i;
    } /* SPLIT-HASH */
    copy(all(c), val[n].begin());
    val[n + 1][m - 1] = -1;
    for (double num; ; ) {
        if (r < n) {
            swap(idx[s], idx[r + m]);
            val[r][s] = 1 / val[r][s];
            for (int j = 0; j <= m; ++j) if (j != s)
                val[r][j] *= -val[r][s];
            for (int i = 0; i <= n + 1; ++i) if (i != r) {
                for (int j = 0; j <= m; ++j) if (j != s)
                    val[i][j] += val[r][j] * val[i][s];
                val[i][s] *= val[r][s];
            }
        } /* SPLIT-HASH */
        r = s = -1;
        for (int j = 0; j < m; ++j)
            if (s < 0 || idx[s] > idx[j])
                if (val[n + 1][j] > eps || val[n + 1][j] > -eps && val[n][j] > eps)
                    s = j;
        if (s < 0) break;
        for (int i = 0; i < n; ++i) if (val[i][s] < -eps) {
            if (r < 0
                || (num = val[r][m] / val[r][s] - val[i][m] / val[i][s]) < -eps
                || num < eps && idx[r + m] > idx[i + m])
                r = i;
        }
        if (r < 0) {
            //    Solution is unbounded.
            return vector<double>{};
        }
    } /* SPLIT-HASH */
    if (val[n + 1][m] < -eps) {
        //    No solution.
        return vector<double>{};
    }
    vector<double> x(m - 1);
    for (int i = m; i < n + m; ++i)
        if (idx[i] < m - 1)
            x[idx[i]] = val[i - m][m];
    return x;
}

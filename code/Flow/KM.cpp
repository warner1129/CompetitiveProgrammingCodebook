// max weight, for min negate the weights
template<class T> // O(N^3), N <= 800
T KM(const vector<vector<T>> &w) {
    const int n = w.size();
    vector<T> lx(n), ly(n);
    vector<int> mx(n, -1), my(n, -1), pa(n);
    auto aug = [&](int y) {
        for (int x, z; y != -1; y = z) {
            x = pa[y]; z = mx[x];
            my[y] = x; mx[x] = y;
        }
    }; /* SPLIT-HASH */
    auto bfs = [&](int s) {
        vector<T> sy(n, inf<T>);
        vector<bool> vx(n), vy(n);
        queue<int> q;
        q.push(s);
        while (true) {
            while (q.size()) {
                int x = q.front(); q.pop();
                vx[x] = 1;
                for (int y = 0; y < n; y++) {
                    if (vy[y]) continue;
                    T d = lx[x] + ly[y] - w[x][y];
                    if (d == 0) {
                        pa[y] = x;
                        if (my[y] == -1)
                            return aug(y);
                        vy[y] = 1;
                        q.push(my[y]);
                    } else if (chmin(sy[y], d)) {
                        pa[y] = x;
                    }
                }
            } /* SPLIT-HASH */
            T cut = inf<T>;
            for (int y = 0; y < n; y++)
                if (!vy[y])
                    chmin(cut, sy[y]);
            for (int j = 0; j < n; j++) {
                if (vx[j]) lx[j] -= cut;
                if (vy[j]) ly[j] += cut;
                else       sy[j] -= cut;
            }
            for (int y = 0; y < n; y++)
                if (!vy[y] and sy[y] == 0) {
                    if (my[y] == -1)
                        return aug(y);
                    vy[y] = 1;
                    q.push(my[y]);
                }
        }
    }; /* SPLIT-HASH */
    for (int x = 0; x < n; x++)
        lx[x] = ranges::max(w[x]);
    for (int x = 0; x < n; x++)
        bfs(x);
    T ans = 0;
    for (int x = 0; x < n; x++)
        ans += w[x][mx[x]];
    return ans;
}

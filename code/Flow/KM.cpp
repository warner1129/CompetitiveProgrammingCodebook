template<class T>
T KM(vector<vector<T>> W) {
    const int n = W.size();
    vector<int> fl(n, -1), fr(n, -1);
    vector<T> hr(n), hl(n);
    for (int i = 0; i < n; i++) {
        hl[i] = ranges::max(W[i]);
    }
    auto bfs = [&](int s) {
        vector<T> slk(n, inf<T>);
        vector<int> pre(n);
        vector<bool> vl(n), vr(n);
        queue<int> que;
        que.push(s);
        vr[s] = true;
        auto check = [&](int x) -> bool {
            vl[x] = true;
            if (fl[x] != -1) {
                que.push(fl[x]);
                return vr[fl[x]] = true;
            }
            while (x != -1) {
                swap(x, fr[fl[x] = pre[x]]);
            }
            return false;
        };
        while (true) {
            while (!que.empty()) {
                int y = que.front();
                que.pop();
                for (int x = 0; x < n; x++) {
                    T d = hl[x] + hr[y] - W[x][y];
                    if (!vl[x] and slk[x] >= d) {
                        pre[x] = y;
                        if (d) {
                            slk[x] = d;
                        } else if (!check(x)) {
                            return;
                        }
                    }
                }
            }
            T d = inf<T>;
            for (int x = 0; x < n; x++) {
                if (!vl[x] and d > slk[x]) {
                    d = slk[x];
                }
            }
            for (int x = 0; x < n; x++) {
                if (vl[x]) {
                    hl[x] += d;
                } else {
                    slk[x] -= d;
                }
                if (vr[x]) {
                    hr[x] -= d;
                }
            }
            for (int x = 0; x < n; x++)
                if (!vl[x] and !slk[x] and !check(x)) {
                    return;
                }
        }
    };
    for (int i = 0; i < n; i++) {
        bfs(i);
    }
    T res = 0;
    for (int i = 0; i < n; i++) {
        res += W[i][fl[i]];
    }
    return res;
}
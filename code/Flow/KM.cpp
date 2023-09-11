i64 KM(vector<vector<int>> W) {
    const int n = W.size();
    vector<int> fl(n, -1), fr(n, -1), hr(n), hl(n);
    for (int i = 0; i < n; ++i) {
        hl[i] = *max_element(W[i].begin(), W[i].end());
    }
    auto Bfs = [&](int s) {
        vector<int> slk(n, INF), pre(n);
        vector<bool> vl(n, false), vr(n, false);
        queue<int> que;
        que.push(s);
        vr[s] = true;
        auto Check = [&](int x) -> bool {
            if (vl[x] = true, fl[x] != -1) {
                que.push(fl[x]);
                return vr[fl[x]] = true;
            }
            while (x != -1) swap(x, fr[fl[x] = pre[x]]);
            return false;
        };
        while (true) {
            while (!que.empty()) {
                int y = que.front(); que.pop();
                for (int x = 0, d = 0; x < n; ++x) {
                    if (!vl[x] and slk[x] >= (d = hl[x] + hr[y] - W[x][y])) {
                        if (pre[x] = y, d) slk[x] = d;
                        else if (!Check(x)) return;
                    }
                }
            }
            int d = INF;
            for (int x = 0; x < n; ++x) {
                if (!vl[x] and d > slk[x]) d = slk[x];
            }
            for (int x = 0; x < n; ++x) {
                if (vl[x]) hl[x] += d;
                else slk[x] -= d;
                if (vr[x]) hr[x] -= d;
            }
            for (int x = 0; x < n; ++x) {
                if (!vl[x] and !slk[x] and !Check(x)) return;
            }
        }
    };
    for (int i = 0; i < n; ++i) Bfs(i);
    i64 res = 0;
    for (int i = 0; i < n; ++i) res += W[i][fl[i]];
    return res;
}

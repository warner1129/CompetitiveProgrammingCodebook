struct HopcroftKarp {
    vector<int> g, l, r;
    int ans;
    HopcroftKarp(int n, int m, const vector<pair<int, int>> &e) 
        : g(e.size()), l(n, -1), r(m, -1), ans(0) {
        vector<int> deg(n + 1);
        for (auto [x, y] : e) deg[x]++;
        partial_sum(all(deg), deg.begin());
        for (auto [x, y] : e) g[--deg[x]] = y;
        vector<int> que(n);
        for (;;) {
            vector<int> a(n, -1), p(n, -1);
            int t = 0;
            for (int i = 0; i < n; i++) if (l[i] == -1)
                que[t++] = a[i] = p[i] = i;
            bool match = false;
            for (int i = 0; i < t; i++) {
                int x = que[i];
                if (~l[a[x]]) continue;
                for (int j = deg[x]; j < deg[x + 1]; j++) {
                    int y = g[j];
                    if (r[y] == -1) {
                        while (~y) r[y] = x, swap(l[x], y), x = p[x];
                        match = true, ans++;
                        break;
                    }
                    if (p[r[y]] == -1)
                    	que[t++] = y = r[y], p[y] = x, a[y] = a[x];
                }
            }
            if (!match) break;
        }
    }
};
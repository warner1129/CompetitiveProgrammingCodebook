// Complexity: O(m sqrt(n))
// edge (u \in A) -> (v \in B) : G[u].push_back(v);
struct HK {
    const int n, m;
    vector<int> l, r, a, p;
    int ans;
    HK(int n, int m) : n(n), m(m), l(n, -1), r(m, -1), ans{} {}
    void work(const auto &G) {
        for (bool match = true; match; ) {
            match = false;
            queue<int> q;
            a.assign(n, -1), p.assign(n, -1);
            for (int i = 0; i < n; i++)
                if (l[i] == -1) q.push(a[i] = p[i] = i);
            while (!q.empty()) {
                int z, x = q.front(); q.pop();
                if (l[a[x]] != -1) continue;
                for (int y : G[x]) {
                    if (r[y] == -1) {
                        for (z = y; z != -1; ) {
                            r[z] = x;
                            swap(l[x], z);
                            x = p[x];
                        }
                        match = true;
                        ans++;
                        break;
                    } else if (p[r[y]] == -1) {
                        q.push(z = r[y]);
                        p[z] = x;
                        a[z] = a[x];
                    }
                }
            }
        }
    }
};

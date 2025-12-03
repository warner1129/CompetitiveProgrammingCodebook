struct GeneralMatching { // n <= 500
    const int BLOCK = 10;
    int n; vector<vector<int>> g;
    vector<int> mat, hit;
    std::priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> unmat;
    GeneralMatching(int _n) : n(_n), g(_n), mat(n, -1), hit(n) {}
    void add_edge(int a, int b) { // 0 <= a != b < n
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int get_match() {
        for (int i = 0; i < n; i++) if (!g[i].empty()) {
            unmat.emplace(0, i);
        }
        // If WA, increase this
        // there are some cases that need >=1.3*n^2 steps for BLOCK=1
        // no idea what the actual bound needed here is.
        const int MAX_STEPS = 10 + 2 * n + n * n / BLOCK / 2;
        mt19937 rng(random_device{}());
        for (int i = 0; i < MAX_STEPS; ++i) {
            if (unmat.empty()) break;
            int u = unmat.top().second;
            unmat.pop();
            if (mat[u] != -1) continue;
            for (int j = 0; j < BLOCK; j++) {
                ++hit[u];
                auto &e = g[u];
                const int v = e[rng() % e.size()];
                mat[u] = v;
                swap(u, mat[v]);
                if (u == -1) break;
            }
            if (u != -1) {
                mat[u] = -1;
                unmat.emplace(hit[u] * 100ULL / (g[u].size() + 1), u);
            }
        }
        int siz = 0;
        for (auto e : mat) siz += (e != -1);
        return siz / 2;
    }
};

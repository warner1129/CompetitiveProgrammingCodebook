template<class Cap>
struct Flow {
    struct Edge { int v; Cap w; int rev; };
    int n; vector<vector<Edge>> G;
    Flow(int _n) : n(_n), G(_n) {}
    void addEdge(int u, int v, Cap w) {
        G[u].push_back({v, w, (int)G[v].size()});
        G[v].push_back({u, 0, (int)G[u].size() - 1});
    } /* SPLIT-HASH */
    vector<int> dep;
    bool bfs(int s, int t) {
        dep.assign(n, 0);
        dep[s] = 1;
        queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (auto [v, w, rev] : G[u])
                if (!dep[v] and w) {
                    dep[v] = dep[u] + 1;
                    que.push(v);
                }
        }
        return dep[t] != 0;
    } /* SPLIT-HASH */
    Cap dfs(int u, Cap in, int t) {
        if (u == t) return in;
        Cap out = 0;
        for (auto &[v, w, rev] : G[u]) {
            if (w and dep[v] == dep[u] + 1) {
                Cap f = dfs(v, min(w, in), t);
                w -= f;
                G[v][rev].w += f;
                in -= f;
                out += f;
                if (!in) break;
            }
        }
        if (in) dep[u] = 0;
        return out;
    } /* SPLIT-HASH */
    Cap maxFlow(int s, int t) {
        Cap ret = 0;
        while (bfs(s, t)) ret += dfs(s, inf<Cap>, t);
        return ret;
    }
};

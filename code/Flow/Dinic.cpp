template<class Cap>
struct Dinic {
    struct Edge { int v; Cap w; int rev; };
    vector<vector<Edge>> G;
    int n, S, T;
    Dinic(int n, int S, int T) : n(n), S(S), T(T), G(n) {}
    void add_edge(int u, int v, Cap w) {
        G[u].push_back({v, w, (int)G[v].size()});
        G[v].push_back({u, 0, (int)G[u].size() - 1});
    }
    vector<int> dep;
    bool bfs() {
        dep.assign(n, 0);
        dep[S] = 1;
        queue<int> que;
        que.push(S);
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (auto [v, w, _] : G[u])
                if (!dep[v] and w) {
                    dep[v] = dep[u] + 1;
                    que.push(v);
                }
        }
        return dep[T] != 0;
    }
    Cap dfs(int u, Cap in) {
        if (u == T) return in;
        Cap out = 0;
        for (auto &[v, w, rev] : G[u]) {
            if (w and dep[v] == dep[u] + 1) {
                Cap f = dfs(v, min(w, in));
                w -= f, G[v][rev].w += f;
                in -= f, out += f;
                if (!in) break;
            }
        }
        if (in) dep[u] = 0;
        return out;
    }
    Cap maxflow() {
        Cap ret = 0;
        while (bfs()) {
            ret += dfs(S, inf<Cap>);
        }
        return ret;
    }
};

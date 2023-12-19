template<class Cap>
struct MCMF {
    struct Edge { int v; Cap f, w; int rev; };
    vector<vector<Edge>> G;
    int n, S, T;
    MCMF(int n, int S, int T) : n(n), S(S), T(T), G(n) {}
    void add_edge(int u, int v, Cap cap, Cap cost) {
        G[u].push_back({v, cap, cost, (int)G[v].size()});
        G[v].push_back({u, 0, -cost, (int)G[u].size() - 1});
    }
    vector<Cap> dis;
    vector<bool> vis;
    bool spfa() {
        queue<int> que;
        dis.assign(n, inf<Cap>);
        vis.assign(n, false);
        que.push(S);
        vis[S] = 1;
        dis[S] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = 0;
            for (auto [v, f, w, _] : G[u])
                if (f and chmin(dis[v], dis[u] + w))
                    if (!vis[v]) que.push(v), vis[v] = 1;
        }
        return dis[T] != inf<Cap>;
    }
    Cap dfs(int u, Cap in) {
        if (u == T) return in;
        vis[u] = 1;
        Cap out = 0;
        for (auto &[v, f, w, rev] : G[u])
            if (f and !vis[v] and dis[v] == dis[u] + w) {
                Cap x = dfs(v, min(in, f));
                in -= x, out += x;
                f -= x, G[v][rev].f += x;
                if (!in) break;
            }
        if (in) dis[u] = inf<Cap>; 
        vis[u] = 0;
        return out;
    }
    pair<Cap, Cap> maxflow() {
        Cap a = 0, b = 0;
        while (spfa()) {
            Cap x = dfs(S, inf<Cap>);
            a += x;
            b += x * dis[T];
        }
        return {a, b};
    }
};
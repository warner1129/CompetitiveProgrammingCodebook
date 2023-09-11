template<class Cap>
struct zkwDinic {
    struct Edge { int v; Cap w, f; int rev; };
    vector<vector<Edge>> G;
    int n, S, T;
    zkwDinic(int _n, int _S, int _T) : n(_n), S(_S), T(_T), G(_n) {}
    void add_edge(int u, int v, Cap w, Cap f) {
        G[u].push_back({v, w, f, (int)G[v].size()});
        G[v].push_back({u, -w, 0, (int)G[u].size() - 1});
    }
    vector<Cap> dis;
    vector<bool> vis;
    bool spfa() {
        queue<int> que;
        dis.assign(n, INF);
        vis.assign(n, false);
        que.push(S);
        vis[S] = 1;
        dis[S] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = 0;
            for (auto [v, w, f, _] : G[u])
                if (f and chmin(dis[v], dis[u] + w))
                    if (!vis[v]) que.push(v), vis[v] = 1;
        }
        return dis[T] != INF;
    }
    Cap dfs(int u, Cap in) {
        if (u == T) return in;
        vis[u] = 1;
        Cap out = 0;
        for (auto &[v, w, f, rev] : G[u])
            if (f and !vis[v] and dis[v] == dis[u] + w) {
                Cap x = dfs(v, min(in, f));
                in -= x, out += x;
                f -= x, G[v][rev].f += x;
                if (!in) break;
            }
        if (in) dis[u] = INF; 
        vis[u] = 0;
        return out;
    }
    pair<Cap, Cap> maxflow() {
        Cap a = 0, b = 0;
        while (spfa()) {
            Cap x = dfs(S, INF);
            a += x;
            b += x * dis[T];
        }
        return {a, b};
    }
};

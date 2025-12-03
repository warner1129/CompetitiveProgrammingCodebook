template<class T>
struct MCMF {
    struct Edge { int v; T f, w; int rev; };
    const int n; vector<vector<Edge>> G;
    MCMF(int _n) : n(_n), G(_n) {}
    void addEdge(int u, int v, T f, T c) {
        G[u].push_back({v, f, c, ssize(G[v])});
        G[v].push_back({u, 0, -c, ssize(G[u]) - 1});
    } /* SPLIT-HASH */
    vector<T> dis;
    vector<bool> vis;
    bool spfa(int s, int t) {
        queue<int> que;
        dis.assign(n, inf<T>);
        vis.assign(n, false);
        que.push(s);
        vis[s] = 1;
        dis[s] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = 0;
            for (auto [v, f, w, _] : G[u])
                if (f and chmin(dis[v], dis[u] + w))
                    if (!vis[v]) {
                        que.push(v);
                        vis[v] = 1;
                    }
        }
        return dis[t] != inf<T>;
    } /* SPLIT-HASH */
    T dfs(int u, T in, int t) {
        if (u == t) return in;
        vis[u] = 1;
        T out = 0;
        for (auto &[v, f, w, rev] : G[u])
            if (f and !vis[v] and dis[v] == dis[u] + w) {
                T x = dfs(v, min(in, f), t);
                in -= x;
                out += x;
                f -= x;
                G[v][rev].f += x;
                if (!in) break;
            }
        if (in) dis[u] = inf<T>; 
        vis[u] = 0;
        return out;
    } /* SPLIT-HASH */
    pair<T, T> maxFlow(int s, int t) {
        T a = 0, b = 0;
        while (spfa(s, t)) {
            T x = dfs(s, inf<T>, t);
            a += x;
            b += x * dis[t];
        }
        return {a, b};
    }
};

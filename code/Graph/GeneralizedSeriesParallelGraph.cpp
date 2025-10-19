/* Vertex:   {u, -1}
 * Edge:     {u, v};             u < v
 * Series:   (e1, v1, e2) => e3; e1 < e2
 * Parallel: (e1, e2)     => e3; e1 = e2
 * Dangling: (v1, e1, v2) => v3; e1 = {v1, v2}
*/   
struct GSPGraph {
    int N;
    vector<pair<int, int>> S;
    vector<vector<int>> tree;
    vector<bool> isrt;
    int getv(int e, int u) { return S[e].ft ^ S[e].sd ^ u; }
    int newNode(pair<int, int> s, vector<int> sub) {
        S[N] = s, tree[N] = sub;
        for (int x : sub) isrt[x] = false;
        return N++;
    }
    GSPGraph(int n, const vector<pair<int, int>> &edge) {
        N = edge.size();
        S = edge;
        S.resize(N * 2 + n, {-1, -1});
        tree.resize(N * 2 + n);
        isrt.assign(N * 2 + n, true);
        vector<vector<int>> G(n);
        vector<int> vid(n), deg(n);
        unordered_map<pair<int, int>, int> eid;
        queue<int> que;
        auto add = [&](int e) {
            auto [u, v] = S[e];
            if (auto it = eid.find(S[e]); it != eid.end()) {
                it->sd = e = newNode(S[e], {e, it->sd});
                if (--deg[u] == 2) que.push(u);
                if (--deg[v] == 2) que.push(v);
            } else eid[S[e]] = e;
            G[u].push_back(e);
            G[v].push_back(e);
        }; /* SPLIT-HASH */
        for (int i = N - 1; i >= 0; i--) {
            S[i] = minmax({S[i].ft, S[i].sd});
            add(i);
        }
        for (int i = 0; i < n; i++) {
            S[vid[i] = N++] = {i, -1};
            deg[i] += ssize(G[i]);
            if (deg[i] <= 2) que.push(i);
        }
        auto pop = [&](int x) {
            while (!isrt[G[x].back()]) G[x].pop_back();
            int e = G[x].back();
            isrt[e] = false;
            return e;
        };
        while (que.size()) {
            int u = que.front(); que.pop();
            if (deg[u] == 1) {
                int e = pop(u), v = getv(e, u);
                vid[v] = newNode(
                    {v, -1}, {vid[S[e].ft], e, vid[S[e].sd]}
                );
                if (--deg[v] == 2) que.push(v);
            } else if (deg[u] == 2) {
                int e1 = pop(u), e2 = pop(u);
                if (S[e1] > S[e2]) swap(e1, e2);
                add(newNode(
                    minmax(getv(e1, u), getv(e2, u)), 
                    {e1, vid[u], e2}
                ));
            }
        }
        S.resize(N);
        tree.resize(N);
        isrt.resize(N);
    }
};

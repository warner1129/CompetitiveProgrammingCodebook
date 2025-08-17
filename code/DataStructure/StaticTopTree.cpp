template<class Vertex, class Path>
struct StaticTopTree {
    enum Type { Rake, Compress, Combine, Convert };
    int stt_root;
    vector<vector<int>> &G;
    vector<int> P, L, R, S;
    vector<Type> T;
    vector<Vertex> f;
    vector<Path> g;
    int buf;
    int dfs(int u) {
        int s = 1, big = 0;
        for (int &v : G[u]) {
            erase(G[v], u);
            int t = dfs(v);
            s += t;
            if (chmax(big, t)) swap(G[u][0], v);
        }
        return s;
    }
    int add(int l, int r, Type t) {
        int x = buf++;
        P[x] = -1, L[x] = l, R[x] = r, T[x] = t;
        if (l != -1) P[l] = x, S[x] += S[l];
        if (r != -1) P[r] = x, S[x] += S[r];
        return x;
    }
    int merge(auto l, auto r, Type t) {
        if (r - l == 1) return *l;
        int s = 0;
        for (auto i = l; i != r; i++) s += S[*i];
        auto m = l;
        while (s > S[*m]) s -= 2 * S[*m++];
        return add(merge(l, m, t), merge(m, r, t), t);
    }
    int pathCluster(int u) {
        vector<int> chs{pointCluster(u)};
        while (!G[u].empty()) chs.push_back(pointCluster(u = G[u][0]));
        return merge(all(chs), Type::Compress);
    }
    int pointCluster(int u) {
        vector<int> chs;
        for (int v : G[u] | views::drop(1)) 
            chs.push_back(add(pathCluster(v), -1, Type::Convert));
        if (chs.empty()) return add(u, -1, Type::Convert);
        return add(u, merge(all(chs), Type::Rake), Type::Combine);
    }
    StaticTopTree(vector<vector<int>> &_G, int root = 0) : G(_G) {
        const int n = G.size();
        P.assign(4 * n, -1);
        L.assign(4 * n, -1);
        R.assign(4 * n, -1);
        S.assign(4 * n, 1);
        T.assign(4 * n, Type::Rake);
        buf = n;
        dfs(root);
        stt_root = pathCluster(root);
        f.resize(buf);
        g.resize(buf);
    }
    void update(int x) {
        if (T[x] == Rake) f[x] = f[L[x]] * f[R[x]];
        else if (T[x] == Compress) g[x] = g[L[x]] + g[R[x]];
        else if (T[x] == Combine) g[x] = f[L[x]] + f[R[x]];
        else if (T[L[x]] == Rake) g[x] = Path(f[L[x]]);
        else f[x] = Vertex(g[L[x]]);
    }
    void set(int x, const Vertex &v) {
        f[x] = v;
        for (x = P[x]; x != -1; x = P[x])
            update(x);
    }
    Vertex get() { return g[stt_root]; }
};
struct Path;
struct Vertex {
    Vertex() {}
    Vertex(const Path&);
};
struct Path {
    Path() {};
    Path(const Vertex&);
};
Vertex operator*(const Vertex &a, const Vertex &b) {
    return {};
}
Path operator+(const Vertex &a, const Vertex &b) {
    return {};
}
Path operator+(const Path &a, const Path &b) {
    return {};
}
Vertex::Vertex(const Path &x) {}
Path::Path(const Vertex &x) {}
/*
 * (root) 1 - 2 (heavy)
 *       / \   \
 *      3  4   5
 * type V: subtree DP info (Commutative Semigroup)
 * type P: path DP info (Semigroup)
 * V(2) + V(5) -> P(2)
 * V(1) + (V(3) * V(4)) -> P(1)
 * ans: V(P(1) + P(2))
*/

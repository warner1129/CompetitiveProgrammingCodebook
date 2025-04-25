template<class Matroid1, class Matroid2>
vector<bool> MatroidIntersection(Matroid1 &m1, Matroid2 &m2) {
    const int N = m1.size();
    vector<bool> I(N);
    while (true) {
        m1.set(I);
        m2.set(I);
        vector<vector<int>> E(N + 2);
        const int s = N, t = N + 1;
        for (int i = 0; i < N; i++) {
            if (I[i]) { continue; }
            auto c1 = m1.circuit(i);
            auto c2 = m2.circuit(i);
            if (c1.empty()) {
                E[s].push_back(i);
            } else {
                for (int y : c1) if (y != i) {
                    E[y].push_back(i);
                }
            }
            if (c2.empty()) {
                E[i].push_back(t);
            } else {
                for (int y : c2) if (y != i) {
                    E[i].push_back(y);
                }
            }
        }
        vector<int> pre(N + 2, -1);
        queue<int> que;
        que.push(s);
        while (que.size() and pre[t] == -1) {
            int u = que.front();
            que.pop();
            for (int v : E[u]) {
                if (pre[v] == -1) {
                    pre[v] = u;
                    que.push(v);
                }
            }
        }
        if (pre[t] == -1) { break; }
        for (int p = pre[t]; p != s; p = pre[p]) {
            I[p] = !I[p];
        }
    }
    return I;
}
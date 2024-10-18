bool inCC(const array<Pt, 3> &p, Pt a) {
    i128 det = 0;
    for (int i = 0; i < 3; i++)
        det += i128(abs2(p[i]) - abs2(a)) * ori(a, p[(i + 1) % 3], p[(i + 2) % 3]);
    return det > 0;
}
struct Edge {
    int id;
    list<Edge>::iterator rit;
};
vector<list<Edge>> Delaunay(const vector<Pt> &P) {
    assert(is_sorted(all(P))); // need sorted before!
    const int n = P.size();
    vector<list<Edge>> E(n);
    auto addEdge = [&](int u, int v) {
        E[u].push_front({v});
        E[v].push_front({u});
        E[u].begin()->rit = E[v].begin();
        E[v].begin()->rit = E[u].begin();
    };
    auto divide = [&](auto &&self, int l, int r) -> void {
        if (r - l <= 1) return;
        if (r - l == 2) return addEdge(l, l + 1);
        int m = (l + r) / 2;
        self(self, l, m);
        self(self, m, r);
        array<int, 2> i{l, m};
        auto go = [&](int t) {
            for (auto e : E[i[t]]) {
                if (ori(P[i[1]], P[i[0]], P[e.id]) > 0 or 
                    PtOnSeg(P[e.id], {P[i[0]], P[i[1]]})) {
                    i[t] = e.id;
                    return true;
                }
            }
            return false;
        };
        while (go(0) or go(1));
        addEdge(i[0], i[1]);
        while (true) {
            array<Pt, 2> x{P[i[0]], P[i[1]]};
            int ch = -1, sd = 0;
            for (int t : {0, 1})
                for (auto e : E[i[t]]) {
                    if (ori(x[0], x[1], P[e.id]) > 0 and 
                        (ch == -1 or inCC({x[0], x[1], P[ch]}, P[e.id]))) {
                        ch = e.id;
                        sd = t;
                    }
                }
            if (ch == -1) break;
            for (auto it = E[i[sd]].begin(); it != E[i[sd]].end(); ) {
                if (strictInter({x[sd], P[it->id]}, {x[sd ^ 1], P[ch]}))
                    E[it->id].erase(it->rit), E[i[sd]].erase(it++);
                else ++it;
            }
            i[sd] = ch;
            addEdge(i[0], i[1]);
        }
    };
    divide(divide, 0, n);
    return E;
}
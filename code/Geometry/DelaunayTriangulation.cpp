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
    auto addEdge = [&](int u, int v, auto a, auto b) {
        a = E[u].insert(a, {v});
        b = E[v].insert(b, {u});
        return array{b->rit = a, a->rit = b};
    };
    auto divide = [&](auto &&self, int l, int r) -> int {
        if (r - l <= 1) return l;
        int m = (l + r) / 2;
        array<int, 2> t{self(self, l, m), self(self, m, r)};
        int w = t[P[t[1]].y < P[t[0]].y];
        auto low = [&](int s) {
            for (Edge e : E[t[s]]) {
                if (ori(P[t[1]], P[t[0]], P[e.id]) > 0 or 
                    PtOnSeg(P[e.id], {P[t[0]], P[t[1]]})) {
                    t[s] = e.id;
                    return true;
                }
            }
            return false;
        };
        while (low(0) or low(1));
        array its = addEdge(t[0], t[1], E[t[0]].begin(), E[t[1]].end());
        while (true) {
            Line L{P[t[0]], P[t[1]]};
            auto cand = [&](int s) -> optional<list<Edge>::iterator> {
                auto nxt = [&](auto it) {
                    if (s == 0) return (++it == E[t[0]].end() ? E[t[0]].begin() : it);
                    return --(it == E[t[1]].begin() ? E[t[1]].end() : it);
                };
                if (E[t[s]].empty()) return {};
                auto lst = nxt(its[s]), it = nxt(lst);
                while (PtSide(P[it->id], L) > 0 and inCC({L.a, L.b, P[lst->id]}, P[it->id])) {
                    E[t[s ^ 1]].erase(lst->rit);
                    E[t[s]].erase(lst);
                    it = nxt(lst = it);
                }
                return PtSide(P[lst->id], L) > 0 ? optional{lst} : nullopt;
            };
            auto lc = cand(0), rc = cand(1);
            if (!lc and !rc) break;
            int sd = !lc or (rc and inCC({L.a, L.b, P[(*lc)->id]}, P[(*rc)->id]));
            auto lst = *(sd ? rc : lc);
            t[sd] = lst->id;
            its[sd] = lst->rit;
            its = addEdge(t[0], t[1], ++its[0], its[1]);
        }
        return w;
    };
    divide(divide, 0, n);
    return E;
};
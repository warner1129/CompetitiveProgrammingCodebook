// {w, u, v}
vector<tuple<int, int, int>> ManhattanMST(vector<Pt> P) {
    vector<int> id(P.size());
    iota(all(id), 0);
    vector<tuple<int, int, int>> edg;
    for (int k = 0; k < 4; k++) {
        sort(all(id), [&](int i, int j) {
                return (P[i] - P[j]).ff < (P[j] - P[i]).ss;
            });
        map<int, int> sweep;
        for (int i : id) {
            auto it = sweep.lower_bound(-P[i].ss);
            while (it != sweep.end()) {
                int j = it->ss;
                Pt d = P[i] - P[j];
                if (d.ss > d.ff) {
                    break;
                }
                edg.emplace_back(d.ff + d.ss, i, j);
                it = sweep.erase(it);
            }
            sweep[-P[i].ss] = i;
        }
        for (Pt &p : P) {
            if (k % 2) {
                p.ff = -p.ff;
            } else {
                swap(p.ff, p.ss);
            }
        }
    }
    return edg;
}
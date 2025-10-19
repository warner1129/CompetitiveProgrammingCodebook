// {w, u, v}
vector<tuple<int, int, int>> ManhattanMST(vector<Pt> P) {
    vector<int> id(P.size());
    iota(all(id), 0);
    vector<tuple<int, int, int>> edg;
    for (int k = 0; k < 4; k++) {
        sort(all(id), [&](int i, int j) {
                return (P[i] - P[j]).ft < (P[j] - P[i]).sd;
            });
        map<int, int> sweep;
        for (int i : id) {
            auto it = sweep.lower_bound(-P[i].sd);
            while (it != sweep.end()) {
                int j = it->sd;
                Pt d = P[i] - P[j];
                if (d.sd > d.ft)
                    break;
                edg.emplace_back(d.ft + d.sd, i, j);
                it = sweep.erase(it);
            }
            sweep[-P[i].sd] = i;
        }
        for (Pt &p : P)
            if (k % 2) p.ft = -p.ft;
            else swap(p.ft, p.sd);
    }
    return edg;
}

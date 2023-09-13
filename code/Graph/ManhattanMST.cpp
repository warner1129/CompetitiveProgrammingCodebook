vector<tuple<int, int, int>> ManhattanMST(vector<Pt> P) {
	vector<int> id(P.size());
	iota(all(id), 0);
	vector<tuple<int, int, int>> edges;
	for (int k = 0; k < 4; ++k) {
		sort(all(id), [&](int i, int j) -> bool {
			return (P[i] - P[j]).ff < (P[j] - P[i]).ss;
		});
		map<int, int> sweep;
		for (int i : id) {
			for (auto it = sweep.lower_bound(-P[i].ss); \
                    it != sweep.end(); sweep.erase(it++)) {
				int j = it->ss;
				Pt d = P[i] - P[j];
				if (d.ss > d.ff) break;
				edges.emplace_back(d.ss + d.ff, i, j);
			}
			sweep[-P[i].ss] = i;
		}
		for (Pt &p : P) {
			if (k % 2) p.ff = -p.ff;
			else swap(p.ff, p.ss);
        }
	}
	return edges;
}

vector<Pt> Minkowski(vector<Pt> P, vector<Pt> Q) {
    auto reorder = [&](auto &R) -> void {
        auto cmp = [&](Pt a, Pt b) -> bool { return Pt(a.ss, a.ff) < Pt(b.ss, b.ff); };
        rotate(R.begin(), min_element(all(R), cmp), R.end());
        R.push_back(R[0]), R.push_back(R[1]);
    };
    const int n = P.size(), m = Q.size();
    reorder(P), reorder(Q);
    vector<Pt> R;
    for (int i = 0, j = 0, s; i < n or j < m; i += (s >= 0), j += (s <= 0)) {
        R.push_back(P[i] + Q[j]);
        s = sig((P[i + 1] - P[i]) ^ (Q[j + 1] - Q[j]));
    }
    return R;
}

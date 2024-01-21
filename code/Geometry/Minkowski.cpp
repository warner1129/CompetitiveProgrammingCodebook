vector<Pt> Minkowski(vector<Pt> P, vector<Pt> Q) { // P, Q need sort
    const int n = P.size(), m = Q.size();
    P.push_back(P[0]), P.push_back(P[1]);
    Q.push_back(Q[0]), Q.push_back(Q[1]);
    vector<Pt> R;
    for (int i = 0, j = 0; i < n or j < m; ) {
        R.push_back(P[i] + Q[j]);
        auto v = (P[i + 1] - P[i]) ^ (Q[j + 1] - Q[j]);
        if (v >= 0) i++;
        if (v <= 0) j++;
    }
    rotate(R.begin(), min_element(all(R)), R.end());
    return R;
}
// O(V^3), undirected graph
// W[i][j] = W[j][i], return {mincut of S-T, S}
template<class T>
pair<T, vector<int>> GlobalMinCut(vector<vector<T>> W) {
    pair<T, vector<int>> best{inf<T>, {}};
    int n = W.size();
    vector<vector<int>> co(n);
    for (int i = 0; i < n; i++) co[i] = {i};
    for (int ph = 1; ph < n; ph++) {
        vector<T> w = W[0];
        int s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) {
            w[t] = -inf<T>; s = t;
            t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += W[t][i];
        }
        best = min(best, {w[t] - W[t][t], co[t]});
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; ++i) W[s][i] += W[t][i];
        for (int i = 0; i < n; ++i) W[i][s] = W[s][i];
        W[0][t] = -inf<T>;
    }
    return best;
}

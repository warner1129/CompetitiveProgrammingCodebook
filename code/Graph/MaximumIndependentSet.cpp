set<int> MI(const vector<vector<int>> &adj) { // n <= 40, (*500)
    set<int> I, V;
    for (int i = 0; i < adj.size(); i++)
        V.insert(i);
    while (!V.empty()) {
        auto it = next(V.begin(), rng() % V.size());
        int cho = *it;
        I.insert(cho);
        V.extract(cho);
        for (int i : adj[cho]) {
            if (auto j = V.find(i); j != V.end())
                V.erase(j);
        }
    }
    return I;
}
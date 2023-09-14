set<int> solve(vector<vector<int>> adj) {
    set<int> I;
    set<int> V;
    for (int i = 0; i < adj.size(); i++) {
        V.insert(i);
    }
    while (!V.empty()) {
        auto it = V.begin();
        int x = (int)(random() * 100) % V.size();
        while(x--) {
            it++;
        }
        int choice = *it;
        I.insert(choice);
        V.erase(V.find(choice));
        for (int i: adj[choice]) {
            if (V.count(i)) {
                V.erase(V.find(i));
            }
        }
    }
    return I;
}
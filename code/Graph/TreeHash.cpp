map<vector<int>, int> id;
vector<vector<int>> sub;
vector<int> siz;
int getid(const vector<int> &T) {
    if (id.count(T)) return id[T];
    int s = 1;
    for (int x : T) {
        s += siz[x];
    }
    sub.push_back(T);
    siz.push_back(s);
    return id[T] = id.size();
}
int dfs(int u, int f) {
    vector<int> S;
    for (int v : G[u]) if (v != f) {
        S.push_back(dfs(v, u));
    }
    sort(all(S));
    return getid(S);
}

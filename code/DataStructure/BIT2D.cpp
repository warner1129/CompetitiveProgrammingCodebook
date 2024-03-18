template <class T>
struct BIT2D {
    vector<vector<T>> val;
    vector<vector<int>> Y;
    vector<int> X;
    int lowbit(int x) { return x & -x; }
    int getp(const vector<int> &v, int x) {
        return upper_bound(all(v), x) - v.begin();
    }
    BIT2D(vector<pair<int, int>> pos) {
        for (auto &[x, y] : pos) {
            X.push_back(x);
            swap(x, y);
        }
        sort(all(pos));
        sort(all(X));
        X.erase(unique(all(X)), X.end());
        Y.resize(X.size() + 1);
        val.resize(X.size() + 1);
        for (auto [y, x] : pos) {
            for (int i = getp(X, x); i <= X.size(); i += lowbit(i))
                if (Y[i].empty() or Y[i].back() != y)
                    Y[i].push_back(y);
        }
        for (int i = 1; i <= X.size(); i++) {
            val[i].assign(Y[i].size() + 1, T{});
        }
    }
    void add(int x, int y, T v) {
        for (int i = getp(X, x); i <= X.size(); i += lowbit(i))
            for (int j = getp(Y[i], y); j <= Y[i].size(); j += lowbit(j))
                val[i][j] += v;
    }
    T qry(int x, int y) {
        T r{};
        for (int i = getp(X, x); i > 0; i -= lowbit(i))
            for (int j = getp(Y[i], y); j > 0; j -= lowbit(j)) {
                r += val[i][j];
            }
        return r;
    }
};

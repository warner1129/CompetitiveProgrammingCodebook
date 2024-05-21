template<class T>
struct SparseTable {
    function<T(T, T)> F;
    vector<vector<T>> st;
    int n;
    SparseTable(const vector<T> &V, const auto &f) {
        F = f;
        n = V.size();
        int lgN = __lg(n);
        st.assign(lgN + 1, vector<T>(n));
        st[0] = V;
        for (int i = 0; i < lgN; i++)
            for (int j = 0; j + (2 << i) <= n; j++)
                st[i + 1][j] = F(st[i][j], st[i][j + (1 << i)]);
    }
    T qry(int l, int r) { // [l, r)
        int h = __lg(r - l);
        return F(st[h][l], st[h][r - (1 << h)]);
    }
};
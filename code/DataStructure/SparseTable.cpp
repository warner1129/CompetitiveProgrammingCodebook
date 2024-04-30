template<class T, auto F>
struct SparseTable {
    int n, lgN;
    vector<vector<T>> st;
    SparseTable(const vector<T> &V) {
        n = V.size();
        lgN = __lg(n);
        st.assign(lgN + 1, vector<T>(n));
        st[0] = V;
        for (int i = 0; (2 << i) <= n; i++) 
            for (int j = 0; j + (2 << i) <= n; j++) {
                st[i + 1][j] = F(st[i][j], st[i][j + (1 << i)]);
            }
    }
    T qry(int l, int r) { // [l, r)
        int h = __lg(r - l);
        return F(st[h][l], st[h][r - (1 << h)]);
    }
};

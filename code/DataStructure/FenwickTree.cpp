template<class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int _n) : n(_n), a(_n) {}
    void add(int p, T x) {
        for (int i = p; i < n; i = i | (i + 1)) {
            a[i] = a[i] + x;
        }
    }
    T qry(int p) { // sum [0, p]
        T s{};
        for (int i = p; i >= 0; i = (i & (i + 1)) - 1) {
            s = s + a[i];
        }
        return s;
    }
    T qry(int l, int r) { // sum [l, r)
        return qry(r - 1) - qry(l - 1);
    }
    pair<int, T> select(T k) { // first position >= k
        T s{};
        int p = 0;
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (p + i <= n and s + a[p + i - 1] < k) {
                p += i;
                s = s + a[p - 1];
            }
        }
        return {p, s};
    }
};
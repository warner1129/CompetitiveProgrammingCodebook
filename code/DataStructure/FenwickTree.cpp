template<class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int _n) : n(_n), a(_n) {}
    int lob(int x) { return x & -x; }
    void add(int p, T x) {
        assert(p < n);
        for (int i = p + 1; i <= n; i += lob(i)) {
            a[i - 1] = a[i - 1] + x;
        }
    }
    T sum(int p) { // sum [0, p]
        T s{};
        for (int i = min(p, n) + 1; i > 0; i -= lob(i)) {
            s = s + a[i - 1];
        }
        return s;
    }
    int findFirst(auto &&pred) { // min{ k | pred(k) }
        T s{};
        int p = 0;
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (p + i <= n and !pred(s + a[p + i - 1])) {
                p += i;
                s = s + a[p - 1];
            }
        }
        return p == n ? -1 : p;
    }
};

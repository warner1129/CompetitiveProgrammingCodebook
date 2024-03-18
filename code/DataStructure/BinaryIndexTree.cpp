template <class T>
struct BIT {
    int n;
    vector<T> a;
    BIT(int n) : n(n), a(n) {}
    int lowbit(int x) { return x & -x; }
    void add(int p, T x) {
        for (int i = p + 1; i <= n; i += lowbit(i))
            a[i - 1] += x;
    }
    T qry(int p) {
        T r{};
        for (int i = p + 1; i > 0; i -= lowbit(i))
            r += a[i - 1];
        return r;
    }
    T qry(int l, int r) { // [l, r)
        return qry(r - 1) - qry(l - 1);
    }
    int kth(T k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (x + i <= n and k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

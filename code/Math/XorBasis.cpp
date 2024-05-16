struct Basis {
    array<int, kD> bas{}, tim{};
    void insert(int x, int t) {
        for (int i = kD - 1; i >= 0; i--)
            if (x >> i & 1) {
                if (!bas[i]) {
                    bas[i] = x;
                    tim[i] = t;
                    return;
                }
                if (t > tim[i]) {
                    swap(x, bas[i]);
                    swap(t, tim[i]);
                }
                x ^= bas[i];
            }
    }
    bool query(int x) {
        for (int i = kD - 1; i >= 0; i--)
            chmin(x, x ^ bas[i]);
        return x == 0;
    }
};
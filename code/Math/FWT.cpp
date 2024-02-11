void solve() {
    int n;
    cin >> n;

    vector<int> f(1 << n);
    vector<int> g(1 << n);
    for (int &x : f) cin >> x;
    for (int &x : g) cin >> x;

    auto OR = [&](auto f, auto g) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                if (j >> i & 1) {
                    f[j] = add(f[j], f[j ^ (1 << i)]);
                    g[j] = add(g[j], g[j ^ (1 << i)]);
                }
        for (int i = 0; i < 1 << n; i++)
            f[i] = mul(f[i], g[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                if (j >> i & 1) {
                    f[j] = add(f[j], mod - f[j ^ (1 << i)]);
                }
        for (int i = 0; i < 1 << n; i++)
            cout << f[i] << " \n"[i == (1 << n) - 1];
    };
    OR(f, g);
    
    auto AND = [&](auto f, auto g) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                if (~j >> i & 1) {
                    f[j] = add(f[j], f[j ^ (1 << i)]);
                    g[j] = add(g[j], g[j ^ (1 << i)]);
                }
        for (int i = 0; i < 1 << n; i++)
            f[i] = mul(f[i], g[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                if (~j >> i & 1) {
                    f[j] = add(f[j], mod - f[j ^ (1 << i)]);
                }
        for (int i = 0; i < 1 << n; i++)
            cout << f[i] << " \n"[i == (1 << n) - 1];
    };
    AND(f, g);

    auto XOR = [&](auto f, auto g) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                if (j >> i & 1) {
                    auto &a = f[j ^ (1 << i)];
                    auto &b = f[j];
                    tie(a, b) = pair(add(a, b), add(a, mod - b));
                    auto &x = g[j ^ (1 << i)];
                    auto &y = g[j];
                    tie(x, y) = pair(add(x, y), add(x, mod - y));
                }
        for (int i = 0; i < (1 << n); i++)
            f[i] = mul(f[i], g[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                if (j >> i & 1) {
                    auto &a = f[j ^ (1 << i)];
                    auto &b = f[j];
                    tie(a, b) = pair(mul(add(a, b), inv2), mul(add(a, mod - b), inv2));
                }
        for (int i = 0; i < 1 << n; i++)
            cout << f[i] << " \n"[i == (1 << n) - 1];
    };
    XOR(f, g);
}
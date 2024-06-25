struct Factorize {
    i64 fmul(i64 a, i64 b, i64 p) {
        return (i128)a * b % p;
    }
    i64 fpow(i64 a, i64 b, i64 p) {
        i64 res = 1;
        for (; b; b >>= 1, a = fmul(a, a, p))
            if (b & 1) res = fmul(res, a, p);
        return res;
    }
    bool check(i64 a, i64 u, i64 n, int t) {
        a = fpow(a, u, n);
        if (a == 0 or a == 1 or a == n - 1) 
            return true;
        for (int i = 0; i < t; i++) {
            a = fmul(a, a, n);
            if (a == 1) return false;
            if (a == n - 1) return true;
        }
        return false;
    };
    bool isPrime(i64 n) {
        constexpr array<i64, 7> magic{2, 235, 9375, 28178, 450775, 9780504, 1795265022};
        // for int: {2, 7, 61}
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        i64 u = n - 1;
        int t = 0;
        while (u % 2 == 0) u >>= 1, t++;
        for (auto v : magic) if (!check(v, u, n, t)) return false;
        return true;
    }
    i64 PollardRho(i64 n) { // return non-trivial factor of n
        if (n % 2 == 0) return 2;
        i64 x = 2, y = 2, d = 1, p = 1;
        auto f = [](i64 x, i64 n, i64 p) -> i64 {
            return ((i128)x * x % n + p) % n;
        };
        while (true) {
            x = f(x, n, p);
            y = f(f(y, n, p), n, p);
            d = gcd(abs(x - y), n);
            if (d != n and d != 1) return d;
            if (d == n) ++p;
        }
    }
    i64 primeFactor(i64 n) {
        return isPrime(n) ? n : primeFactor(PollardRho(n));
    }
};
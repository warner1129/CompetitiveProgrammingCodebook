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
    bool MillerRabin(i64 n) {
        auto Check = [&](i64 a, i64 u, i64 n, int t) -> bool {
            a = fpow(a, u, n);
            if (a == 0 or a == 1 or a == n - 1) return true;
            for (int i = 0; i < t; i++) {
                a = fmul(a, a, n);
                if (a == 1) return false;
                if (a == n - 1) return true;
            }
            return false;
        };

        auto IsPrime = [&](i64 n) -> bool {
            constexpr array<i64, 7> kChk{2, 235, 9375, 28178, 450775, 9780504, 1795265022};
            // for int: {2, 7, 61}
            if (n < 2) return false;
            if (n % 2 == 0) return n == 2;
            i64 u = n - 1;
            int t = 0;
            while (u % 2 == 0) u >>= 1, t++;
            for (auto v : kChk) if (!Check(v, u, n, t)) return false;
            return true;
        };
        return IsPrime(n);
    }
    i64 PollardRho(i64 n) {
        if (n % 2 == 0) return 2;
        i64 x = 2, y = 2, d = 1, p = 1;
        auto f = [](i64 x, i64 n, i64 p) -> i64 {
            return ((i128)x * x % n + p) % n;
        };
        while (true) {
            x = f(x, n, p);
            y = f(f(y, n, p), n, p);
            d = __gcd(abs(x - y), n);
            if (d != n and d != 1) return d;
            if (d == n) ++p;
        }
    }
};

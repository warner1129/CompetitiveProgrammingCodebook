// Prefix Sums of Multiplicative Functions
// O(N^0.75 / logN)
// calc f(1) + ... + f(N)
// where f is multiplicative function
// construct completely multiplicative functions 
// g_i s.t. for all prime x, f(x) = sigma c_i*g_i(x)
// def gsum(x) = g(1) + ... + g(x)
// call apply(g_i, gsum_i, c_i) and call work(f)
struct Min25 {
    const i64 N, sqrtN;
    vector<i64> Q;
    vector<i64> Fp, S;
    int id(i64 x) { return x <= sqrtN ? Q.size() - x : N / x - 1; }
    Min25(i64 N) : N(N), sqrtN(isqrt(N)) {
        // sieve(sqrtN);
        for (i64 l = 1, r; l <= N; l = r + 1) {
            Q.push_back(N / l);
            r = N / (N / l);
        }
        Fp.assign(Q.size(), 0);
        S.assign(Q.size(), 0);
    }
    void apply(const auto &f, const auto &fsum, i64 coef) {
        vector<i64> F(Q.size());
        for (int i = 0; i < Q.size(); i++) {
            F[i] = fsum(Q[i]) - 1;
        }
        for (i64 p : primes) {
            auto t = F[id(p - 1)];
            for (int i = 0; i < Q.size(); i++) {
                if (Q[i] < p * p) {
                    break;
                }
                F[i] -= (F[id(Q[i] / p)] - t) * f(p);
            }
        }
        for (int i = 0; i < Q.size(); i++) {
            Fp[i] += F[i] * coef;
        }
    }
    i64 work(const auto &f) {
        S = Fp;
        for (i64 p : primes | views::reverse) {
            i64 t = Fp[id(p)];
            for (int i = 0; i < Q.size(); i++) {
                if (Q[i] < p * p) {
                    break;
                }
                for (i64 pw = p; pw * p <= Q[i]; pw *= p) {
                    S[i] += (S[id(Q[i] / pw)] - t) * f(p, pw);
                    S[i] += f(p, pw * p);
                }
            }
        }
        for (int i = 0; i < Q.size(); i++) {
            S[i]++;
        }
        return S[0];
    }
};
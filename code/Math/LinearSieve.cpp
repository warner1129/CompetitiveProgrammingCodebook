template<size_t N>
struct Sieve {
    array<bool, N + 1> isp{};
    array<int, N + 1> mu{}, phi{};
    vector<int> primes{};
    Sieve() {
        isp.fill(true);
        isp[0] = isp[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isp[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
            }
            for (i64 p : primes) {
                if (p * i > N) break;
                isp[p * i] = false;
                if (i % p == 0) {
                    phi[p * i] = phi[i] * p;
                    break;
                }
                phi[p * i] = phi[i] * (p - 1);
                mu[p * i] = mu[p] * mu[i];
            }
        }
    }
};
vector<int> primes, minp;
vector<int> mu, phi;
vector<bool> isp;
void Sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    isp.assign(n + 1, 0);
    mu.resize(n + 1);
    phi.resize(n + 1);
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            isp[i] = 1;
            primes.push_back(i);
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (i64 p : primes) {
            if (p * i > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                phi[p * i] = phi[i] * p;
                break;
            }
            phi[p * i] = phi[i] * (p - 1);
            mu[p * i] = mu[p] * mu[i];
        }
    }
}
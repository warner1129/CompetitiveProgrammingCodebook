/*
 * Returns min_{x=0}^{n - 1} (ax + b) mod m
 * Require: n, m > 0, 0 <= a, b < m
 */
int LinearModMin(int n, int m, int a, int b, 
                 int cnt = 1, int p = 1, int q = 1) {
    if (!a) return b;
    int z = cnt & 1;
    if ((z and b >= a) or (!z and b < m-a)) {
        int t = (m - b + a * z - 1) / a;
        int c = (t - z) * p + q * z;
        if (n <= c) return z ? b : a * ((n - 1) / p) + b;
        n -= c, b += a * t - m * z;
    } /* SPLIT-HASH */
    b = (z ? a : m) - 1 - b;
    cnt++;
    int d = m / a;
    int c = LinearModMin(n, a, m % a, 
                         b, cnt, (d - 1) * p + q, d * p + q);
    return cnt & 1 ? m - 1 - c : a - 1 - c;
}

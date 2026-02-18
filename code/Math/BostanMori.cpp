// [x^k](P/Q)
i64 BostanMori(i64 k, vector<i64> P, vector<i64> Q) {
    const int d = Q.size() - 1;
    vector<i64> nQ(d + 1);
    while (k) {
        for (int i = 0; i <= d; i++)
            nQ[i] = (i % 2) ? -Q[i] : Q[i];
        P = P * nQ; Q = Q * nQ;
        for (int i = 0; i <= d; i++)
            Q[i] = Q[i * 2];
        Q.resize(d + 1);
        int m = 0;
        for (int i = k & 1; i < ssize(P); i += 2) 
            P[m++] = P[i];
        P.resize(m);
        if (P.empty()) P = {0}; k /= 2;
    }
    return P[0] * inv(Q[0]) % mod;
}

struct SuffixArray {
    int n;
	vector<int> suf, rk, S;
	SuffixArray(vector<int> _S) : S(_S) {
        n = S.size();
        suf.assign(n, 0);
        rk.assign(n * 2, -1);
		iota(all(suf), 0);
		for (int i = 0; i < n; i++) rk[i] = S[i];
		for (int k = 2; k < n + n; k *= 2) {
			auto cmp = [&](int a, int b) -> bool {
				return rk[a] == rk[b] ? (rk[a + k / 2] < rk[b + k / 2]) : (rk[a] < rk[b]);
			};
			sort(all(suf), cmp);
			auto tmp = rk;
			tmp[suf[0]] = 0;
			for (int i = 1; i < n; i++) {
                tmp[suf[i]] = tmp[suf[i - 1]] + cmp(suf[i - 1], suf[i]);
            }
			rk.swap(tmp);
		}
	}
};

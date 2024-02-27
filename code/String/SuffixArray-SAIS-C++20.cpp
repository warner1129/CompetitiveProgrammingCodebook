auto sais(const auto &s) {
    const int n = (int)s.size(), z = ranges::max(s) + 1;
    if (n == 1) return vector{0};
    vector<int> c(z); for (int x : s) ++c[x];
    partial_sum(all(c), begin(c));
    vector<int> sa(n); auto I = views::iota(0, n);
    vector<bool> t(n); t[n - 1] = true;
    for (int i = n - 2; i >= 0; i--) 
        t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
    auto is_lms = views::filter([&t](int x) {
            return x && t[x] & !t[x - 1]; });
    auto induce = [&] {
        for (auto x = c; int y : sa)
            if (y--) if (!t[y]) sa[x[s[y] - 1]++] = y;
        for(auto x = c; int y : sa | views::reverse)
            if (y--) if (t[y]) sa[--x[s[y]]] = y;
    };
    vector<int> lms, q(n); lms.reserve(n);
    for (auto x = c; int i : I | is_lms) {
        q[i] = int(lms.size());
        lms.push_back(sa[--x[s[i]]] = i);
    }
    induce(); vector<int> ns(lms.size());
    for (int j = -1, nz = 0; int i : sa | is_lms) {
        if (j >= 0) {
            int len = min({n - i, n - j, lms[q[i] + 1] - i});
            ns[q[i]] = nz += lexicographical_compare(
                    begin(s) + j, begin(s) + j + len,
                    begin(s) + i, begin(s) + i + len);
        }
        j = i;
    }
    ranges::fill(sa, 0); auto nsa = sais(ns);
    for (auto x = c; int y : nsa | views::reverse)
        y = lms[y], sa[--x[s[y]]] = y;
    return induce(), sa;
}
// SPLIT_HASH_HERE sa[i]: sa[i]-th suffix is the
// i-th lexicographically smallest suffix.
// hi[i]: LCP of suffix sa[i] and suffix sa[i - 1].
struct Suffix {
    int n; vector<int> sa, hi, rev;
    Suffix(const auto &s) : n(int(s.size())),
        hi(n), rev(n) {
        vector<int> _s(n + 1); // _s[n] = 0
        copy(all(s), begin(_s)); // s shouldn't contain 0
        sa = sais(_s); sa.erase(sa.begin());
        for (int i = 0; i < n; i++) rev[sa[i]] = i;
        for (int i = 0, h = 0; i < n; i++) {
            if (!rev[i]) { h = 0; continue; }
            for (int j = sa[rev[i] - 1]; i + h < n && j + h < n
                    && s[i + h] == s[j + h];) ++h;
            hi[rev[i]] = h ? h-- : 0;
        }
    }
};
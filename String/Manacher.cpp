vector<int> manacher(const string &s) {
    string p = "@#";
    for (char c : s) {
        p += c;
        p += '#';
    }
    p += '$';
    vector<int> dp(p.size());
    int mid = 0, r = 1;
    for (int i = 1; i < p.size() - 1; i++) {
        auto &k = dp[i];
        k = i < mid + r ? min(dp[mid * 2 - i], mid + r - i) : 0;
        while (p[i + k + 1] == p[i - k - 1]) k++;
        if (i + k > mid + r) {
            mid = i;
            r = k;
        }
    }
    return vector<int>(dp.begin() + 2, dp.end() - 2);
}

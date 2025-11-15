vector<int> manacher(string_view s) {
    string p = "@#";
    for (char c : s) { p += c; p += '#'; }
    p += '$';
    vector<int> dp(p.size());
    int m = 0, r = 1;
    for (int i = 1; i < p.size() - 1; i++) {
        auto &k = dp[i];
        k = i < m + r ? min(dp[m * 2 - i], m + r - i) : 0;
        while (p[i + k + 1] == p[i - k - 1]) k++;
        if (i + k > m + r) m = i, r = k; 
    }
    return vector<int>(dp.begin() + 2, dp.end() - 2);
}

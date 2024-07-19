vector<int> buildFail(string s) {
    const int len = s.size();
    vector<int> f(len, -1);
    for (int i = 1, p = -1; i < len; i++) {
        while (~p and s[p + 1] != s[i]) p = f[p];
        if (s[p + 1] == s[i]) p++;
        f[i] = p;
    }
    return f;
}
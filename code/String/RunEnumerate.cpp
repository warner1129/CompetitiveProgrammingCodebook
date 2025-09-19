// Returns all runs of s as vector of {p, l, r}, which means that period of s[l, r - 1] is p
vector<array<int, 3>> RunEnumerate(string s) {
    const int n = s.size();
    vector<array<int, 3>> runs;
    RollingHash rh(s);
    for (int inv : {0, 1}) {
        vector<int> stk{n};
        for (int i = n - 1; i >= 0; i--) {
            int j;
            while ((j = stk.back()) != n) {
                int k = stk.rbegin()[1], l = min({rh.lcp(i, j), j - i, k - j});
                if ((i + l == j and j + l == k)
                    or (j + l == k) 
                    or (i + l != j and (s[i + l] > s[j + l]) ^ inv)) {
                    break;
                }
                stk.pop_back();
            }
            stk.push_back(i);
            int l = i - rh.lcs(i - 1, j - 1), r = j + rh.lcp(i, j);
            if (r - l >= 2 * (j - i)) {
                runs.push_back({j - i, l, r});
            }
        }
    }
    sort(all(runs));
    runs.erase(unique(all(runs)), runs.end());
    return runs;
};

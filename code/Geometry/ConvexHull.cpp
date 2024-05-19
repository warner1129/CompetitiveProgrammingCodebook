vector<Pt> Hull(vector<Pt> P) {
    sort(all(P));
    P.erase(unique(all(P)), P.end());
    P.insert(P.end(), P.rbegin() + 1, P.rend());
    vector<Pt> stk;
    for (auto p : P) {
        while (stk.size() >= 2 and \             // < if reserve co-line 
                cro(*++stk.rbegin(), stk.back(), p) <= 0 and \
                (*++stk.rbegin() < stk.back()) == (stk.back() < p)) {
            stk.pop_back();
        }
        stk.push_back(p);
    }
    stk.pop_back();
    return stk;
}
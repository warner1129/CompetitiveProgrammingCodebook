struct BigBinary : map<int, int> {
    void split(int x) {
        auto it = lower_bound(x);
        if (it != begin()) {
            it--;
            if (it->ss > x) {
                (*this)[x] = it->ss;
                it->ss = x;
            }
        }
    }
    void add(int x) {
        split(x);
        auto it = find(x);
        while (it != end() and it->ff == x) {
            x = it->ss;
            it = erase(it);
        }
        (*this)[x] = x + 1;
    }
    void sub(int x) {
        split(x);
        auto it = lower_bound(x);
        // assert(it != end());
        auto [l, r] = *it;
        erase(it);
        if (l + 1 < r)  (*this)[l + 1] = r;
        if (x < l)      (*this)[x] = l;
    }
};

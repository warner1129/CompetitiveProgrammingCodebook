template<class T, class Comp = less<T>>
struct DynamicHull {
    set<T, Comp> H;
    DynamicHull() {}
    void insert(T p) {
        if (inside(p)) return;
        auto it = H.insert(p).ff;
        while (it != H.begin() and prev(it) != H.begin() \
                and cross(*prev(it, 2), *prev(it), *it) <= 0) {
            it = H.erase(--it);
        }
        while (it != --H.end() and next(it) != --H.end() \
                and cross(*it, *next(it), *next(it, 2)) <= 0) {
            it = --H.erase(++it);
        }
    }
    bool inside(T p) {
        auto it = H.lower_bound(p);
        if (it == H.end()) return false;
        if (it == H.begin()) return p == *it;
        return cross(*prev(it), p, *it) <= 0;
    }
};

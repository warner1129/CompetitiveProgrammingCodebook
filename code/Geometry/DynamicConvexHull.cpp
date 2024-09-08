template<class T, class Comp = less<T>>
struct DynamicHull {
    set<T, Comp> H;
    void insert(T p) {
        if (inside(p)) return;
        auto it = H.insert(p).ff;
        while (it != H.begin() and prev(it) != H.begin() \
                and ori(*prev(it, 2), *prev(it), *it) <= 0) {
            it = H.erase(--it);
        }
        while (it != --H.end() and next(it) != --H.end() \
                and ori(*it, *next(it), *next(it, 2)) <= 0) {
            it = --H.erase(++it);
        }
    }
    int inside(T p) { // 0: out, 1: on, 2: in
        auto it = H.lower_bound(p);
        if (it == H.end()) return 0;
        if (it == H.begin()) return p == *it;
        return 1 - sgn(ori(*prev(it), p, *it));
    }
};
// DynamicHull<Pt> D;
// DynamicHull<Pt, greater<>> U;
// D.inside(p) and U.inside(p)
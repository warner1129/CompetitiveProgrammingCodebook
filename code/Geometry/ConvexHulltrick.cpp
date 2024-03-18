template <class T>
struct Convex {
    int n; 
    vector<T> A, V, L, U;
    Convex(const vector<T> &_A) : A(_A), n(_A.size()) { // n >= 3
        auto it = max_element(all(A));
        L.assign(A.begin(), it + 1);
        U.assign(it, A.end()), U.push_back(A[0]);
        for (int i = 0; i < n; i++) {
            V.push_back(A[(i + 1) % n] - A[i]);
        }
    }
    int inside(T p, const vector<T> &h, auto f) { // 0: out, 1: on, 2: in
        auto it = lower_bound(all(h), p, f);
        if (it == h.end()) return 0;
        if (it == h.begin()) return p == *it;
        return 1 - sig(cro(*prev(it), p, *it));
    }
    int inside(T p) {
        return min(inside(p, L, less{}), inside(p, U, greater{}));
    }
    static bool cmp(T a, T b) { return sig(a ^ b) > 0; }
    int tangent(T v, bool close = true) {
        assert(v != T{});
        auto l = V.begin(), r = V.begin() + L.size() - 1;
        if (v < T{}) l = r, r = V.end();
        if (close) return (lower_bound(l, r, v, cmp) - V.begin()) % n;
        return (upper_bound(l, r, v, cmp) - V.begin()) % n;
    } 
    array<int, 2> tangent2(T p) {
        array<int, 2> t{-1, -1};
        if (inside(p) == 2) return t;
        if (auto it = lower_bound(all(L), p); it != L.end() and p == *it) {
            int s = it - L.begin();
            return {(s + 1) % n, (s - 1 + n) % n};
        }
        if (auto it = lower_bound(all(U), p, greater{}); it != U.end() and p == *it) {
            int s = it - U.begin() + L.size() - 1;
            return {(s + 1) % n, (s - 1 + n) % n};
        }
        for (int i = 0; i != t[0]; i = tangent((A[t[0] = i] - p), 0));
        for (int i = 0; i != t[1]; i = tangent((p - A[t[1] = i]), 1));
        return t;
    }
    int Find(int l, int r, T a, T b) {
        if (r < l) r += n;
        int s = sig(cro(a, b, A[l % n]));
        while (r - l > 1) {
            (sig(cro(a, b, A[(l + r) / 2 % n])) == s ? l : r) = (l + r) / 2;
        }
        return l % n;
    };
    vector<int> LineIntersect(T a, T b) { // A_x A_x+1 interset with ab 
        assert(a != b);
        int l = tangent(a - b), r = tangent(b - a);
        if (sig(cro(a, b, A[l])) * sig(cro(a, b, A[r])) >= 0) return {};
        return {Find(l, r, a, b), Find(r, l, a, b)};
    }
};
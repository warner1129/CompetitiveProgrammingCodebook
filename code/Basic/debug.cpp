template<class F, class S>
ostream& operator<<(ostream& s, const pair<F, S>& v) {
    return s << "(" << v.first << ", " << v.second << ")";
}
template<ranges::range T> requires (!is_convertible_v<T, string_view>)
ostream& operator<<(ostream& s, T&& v) { 
    auto e = ""; s << '[';
    for (auto &&x : v) s << e << x, e = ", ";
    return s << ']';
}
template<class... T> void dbg(T... x) {
#ifdef LOCAL
    char e{};
    ((cerr << e << x, e = ' '), ...);
    cerr << '\n';
#endif
}
#define debug(x...) dbg(#x, '=', x)

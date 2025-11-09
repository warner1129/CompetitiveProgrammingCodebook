template<class F, class S>
ostream& operator<<(ostream& s, const pair<F, S>& v) {
    return s << "(" << v.ft << ", " << v.sd << ")"; }
template<ranges::range T>
requires (!is_convertible_v<T, string_view>)
ostream& operator<<(ostream& s, T&& v) { 
    auto e = ""; bool ie = &s == &cerr; if (ie) s << '[';
    for (auto &&x : v) s << e << x, e = ie ? ", " : " ";
    if (ie) s << ']'; return s; }
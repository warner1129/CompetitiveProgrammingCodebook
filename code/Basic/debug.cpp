template<class... T> void dbg(T... x) {
#ifdef LOCAL
    char e{};
    ((cerr << e << x, e = ' '), ...);
    cerr << '\n';
#endif
}
#define debug(x...) dbg(#x, '=', x)

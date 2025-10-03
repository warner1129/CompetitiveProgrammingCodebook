template <class... T>
void dbg(const T&... xs) {
#ifdef LOCAL
    char e{}; using U = int[];
    (void)U{0, ((cerr << e << xs, e = ' '), 0)...};
    cerr << '\n';
#endif
}
#define debug(x...) dbg(#x, '=', x)

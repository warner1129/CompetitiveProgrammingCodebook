#include <bits/stdc++.h>
using namespace std;
template<ranges::range T,
        class = enable_if_t<!is_convertible_v<T, string_view>>>
istream& operator>>(istream &s, T &&v) { 
    for (auto &&x : v) s >> x; return s;
}
template<ranges::range T, 
        class = enable_if_t<!is_convertible_v<T, string_view>>>
ostream& operator<<(ostream &s, T &&v) { 
    for (auto &&x : v) s << x << ' '; return s;
}
#ifdef LOCAL
template<class... T> void dbg(T... x) { char e{}; ((cerr << e << x, e = ' '), ...); }
#define debug(x...) dbg(#x, '=', x, '\n')
#else
#define debug(...) ((void)0)
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
template<class T> bool chmin(T &a, T b) { return (b < a and (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }
template<class T> inline constexpr T inf = numeric_limits<T>::max() / 2;
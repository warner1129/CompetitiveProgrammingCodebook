#include <bits/stdc++.h>
using namespace std;
template<class F, class S>
ostream &operator<<(ostream &s, const pair<F, S> &v) {
    return s << "(" << v.first << ", " << v.second << ")";
}
template<ranges::range T> requires (!is_convertible_v<T, string_view>)
istream &operator>>(istream &s, T &&v) { 
    for (auto &&x : v) s >> x; 
    return s; 
}
template<ranges::range T> requires (!is_convertible_v<T, string_view>)
ostream &operator<<(ostream &s, T &&v) { 
    for (auto &&x : v) s << x << ' '; 
    return s; 
}
#ifdef LOCAL
template<class... T> void dbg(T... x) {
    char e{};
    ((cerr << e << x, e = ' '), ...);
}
#define debug(x...) dbg(#x, '=', x, '\n')
#else
#define debug(...) ((void)0)
#endif
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define ff first
#define ss second
template<class T> inline constexpr T inf = numeric_limits<T>::max() / 2;
bool chmin(auto &a, auto b) { return (b < a) and (a = b, true); }
bool chmax(auto &a, auto b) { return (a < b) and (a = b, true); }
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
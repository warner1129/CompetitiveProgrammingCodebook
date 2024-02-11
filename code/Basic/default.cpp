#include <bits/stdc++.h>
using namespace std;
template<ranges::range T, class = enable_if_t<!is_convertible_v<T, string_view>>>
istream& operator>>(istream &s, T &&v) { for (auto &&x : v) s >> x; return s; }
template<ranges::range T, class = enable_if_t<!is_convertible_v<T, string_view>>>
ostream& operator<<(ostream &s, T &&v) { for (auto &&x : v) s << x << ' '; return s; }
#ifdef LOCAL
template<class... T> void dbg(T... x) { char e{}; ((cerr << e << x, e = ' '), ...); }
#define debug(x...) dbg(#x, '=', x, '\n')
#else
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define debug(...) ((void)0)
#endif
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define ff first
#define ss second
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
template<class T> bool chmin(T &a, T b) { return (b < a and (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }
template<class T> inline constexpr T inf = numeric_limits<T>::max() / 2;
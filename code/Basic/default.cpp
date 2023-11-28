#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
template <class... T> void dbg(T... x) { char e{}; ((cerr << e << x, e = ' '), ...); }
template <class T> void org(T l, T r) { while (l != r) cerr << ' ' << *l++; cerr << '\n'; }
#define debug(x...) dbg(#x, '=', x, '\n')
#define olist(x...) dbg(#x, '='), org(x)
#else
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define debug(...) ((void)0)
#define olist(...) ((void)0)
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
template <class T> inline constexpr T inf = numeric_limits<T>::max() / 2;
constexpr int mod = 998244353;
template<class T> bool chmin(T &a, T b) { return (b < a and (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }
template<class... T> int add(T... x) { int t{}; return (((t += x) %= mod), ...), t; }
template<class... T> int mul(T... x) { i64 t{1}; return (((t *= x) %= mod), ...), t; }
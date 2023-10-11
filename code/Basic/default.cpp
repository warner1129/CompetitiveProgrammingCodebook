#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
template<class... T> void dbg(T... x) { char e{}; ((cerr << e << x, e = ' '), ...); }
template<class T> void org(T l, T r) { while (l != r) cerr << ' ' << *l++; cerr << '\n'; }
#define debug(x...) dbg(#x, '=', x, '\n')
#define orang(x...) dbg(#x, '='), org(x)
#else
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define debug(...) ((void)0)
#define orange(...) ((void)0)
#endif
#define ff first
#define ss second
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
template<class T> bool chmin(T &a, T b) { return b < a and (a = b, true); }
template<class T> bool chmax(T &a, T b) { return a < b and (a = b, true); }
template<class ...T> int add(T ...x) { int t{}; return (((t += x) %= mod), ...), t; }
template<class ...T> int mul(T ...x) { i64 t{1}; return (((t *= x) %= mod), ...), t; } 
#include <bits/stdc++.h>
 
using namespace std;
 
#ifdef LOCAL
template<class A, class B>
ostream& operator<<(ostream &os, pair<A, B> p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<class ...T> void dbg(T ...x) { char e{}; ((cerr << e << x, e = ' '), ...); }
template<class T> void org(T l, T r) { while (l != r) cerr << ' ' << *l++; cerr << '\n'; }
#define debug(args...) dbg("(", #args, ") =", args, '\n')
#define orange(args...) dbg("[", #args, ") ="), org(args)
#else
#define debug(...) (0)
#define orange(...) (0)
#endif
template<class T> bool chmin(T &a, T b) { return b < a and (a = b, true); }
template<class T> bool chmax(T &a, T b) { return a < b and (a = b, true); }
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define ff first
#define ss second

using i64 = long long;
using u64 = unsigned long long;

constexpr int mod = 998244353;
template<class ...T> int add(T ...x) { int t{}; return (((t += x) %= mod), ...), t; } 
template<class ...T> int mul(T ...x) { i64 t{1}; return (((t *= x) %= mod), ...), t; }

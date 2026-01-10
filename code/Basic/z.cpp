#include <bits/stdc++.h>
using namespace std;

template<ranges::range T> 
requires (!is_convertible_v<T, string_view>)
ostream& operator<<(ostream& s, T&& v);

template<class F, class S>
ostream& operator<<(ostream& s, const pair<F, S>& v) {
    return s << "(" << v.first << ", " << v.second << ")";
}

template<ranges::range T> 
requires (!is_convertible_v<T, string_view>)
ostream& operator<<(ostream& s, T&& v) {
    auto e = ""; bool ie = &s == &cerr; if (ie) s << '[';
    for (auto &&x : v) s << e << x, e = ie ? ", " : " ";
    if (ie) s << "]";
    return s;
}

void dbg(auto&& ...x) {
#ifdef LOCAL
    char e{};
    ((cerr << e << x, e = ' '), ...);
    cerr << '\n';
#endif
}
#define debug(x...) dbg(#x, '=', x)

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define ft first
#define sd second

template <class T> inline constexpr T inf = numeric_limits<T>::max() / 2;
bool chmin(auto &a, auto b) { return (b < a) and (a = b, true); }
bool chmax(auto &a, auto b) { return (a < b) and (a = b, true); }

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

void solve() {
    int x = 0;
    debug(x);
}

int main() {
#ifndef LOCAL
    cin.tie(0)->sync_with_stdio(false);
#endif
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

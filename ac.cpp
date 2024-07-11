#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<class T> bool chmin(T &a, T b) { return (b < a) and (a = b, true); }
template<class T> bool chmax(T &a, T b) { return (a < b) and (a = b, true); }

const int kC = 100;
int dp[kC][kC][2]{};
int cnt[kC][kC][2]{};
bool vis[kC][kC][2]{};

void solve() {
    int n, m;
    cin >> n >> m;
    cerr << n << '\n';

    vector G(n, vector<int>{});
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[v].push_back(u);
        deg[u]++;
    }

    int A, B;
    cin >> B >> A;
    A--, B--;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            for (int k : {0, 1}) {
                dp[i][j][k] = 1;
                cnt[i][j][k] = 0;
                vis[i][j][k] = 0;
            }
        }

    queue<array<int, 3>> que;
    for (int a = 0; a < n; a++) {
        dp[a][a][0] = 1;
        dp[a][a][1] = 0;
        que.push({a, a, 0});
        que.push({a, a, 1});
        vis[a][a][0] = vis[a][a][1] = 1;
    }

    for (int a = 0; a < n; a++)
        for (int b = 0; b < n; b++) if (a != b) {
            if (deg[a] == 0) {
                dp[a][b][1] = 1;
                que.push({a, b, 1});
                vis[a][b][1] = 1;
            }
            if (deg[b] == 0) {
                dp[a][b][0] = 1;
                que.push({a, b, 0});
                vis[a][b][0] = 1;
            }
        }

    auto push = [&](int a, int b, int d) {
        if (vis[a][b][d]) return;
        if (cnt[a][b][d] == deg[d == 0 ? b : a]) {
            vis[a][b][d] = 1;
            que.push({a, b, d});
        }
    };

    while (que.size()) {
        auto [a, b, p] = que.front();
        // cerr << "a = " << a << " b = " << b << " p = " << p << '\n';
        // cerr << "dp = " << dp[a][b][p] << '\n';
        que.pop();
        if (p == 0) {
            for (int c : G[a]) {
                if (vis[c][b][p ^ 1]) continue;
                cnt[c][b][p ^ 1]++;
                if (dp[a][b][p] == 1) {
                    dp[c][b][p ^ 1] = 0;
                }
                push(c, b, p ^ 1);
            }
        } else {
            for (int c : G[b]) {
                if (vis[a][c][p ^ 1]) continue;
                cnt[a][c][p ^ 1]++;
                if (dp[a][b][p] == 1) {
                    dp[a][c][p ^ 1] = 0;
                }
                push(a, c, p ^ 1);
            }
        }
    }

    if (!vis[A][B][0] or dp[A][B][0] == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

}

signed main() {
    cin.tie(0)->sync_with_stdio(false);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}

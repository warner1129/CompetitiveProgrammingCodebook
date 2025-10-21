template<class Info> 
struct Wavelet {
    int N, lgN;
    vector<vector<int>> cnt;
    vector<vector<Info>> sum;
    Wavelet(vector<pair<int, Info>> d) {
        N = d.size(); lgN = __lg(N);
        cnt.assign(lgN + 1, vector<int>(N + 1));
        sum.assign(lgN + 1, vector<Info>(N + 1));
        for (int k = lgN; k >= 0; k--) {
            for (int i = 0; i < N; i++) {
                auto [rk, val] = d[i];
                rk = ~rk >> k & 1;
                val = rk ? val : Info{};
                cnt[k][i + 1] = cnt[k][i] + rk;
                sum[k][i + 1] = sum[k][i] + val;
            }
            ranges::stable_partition(d, [&](auto &e) {
                return ~e.first >> k & 1;
            });
        }
    }
    pair<int, Info> findFirst(int x, int y, auto &&pred, Info cur = {}) {
        int ans = 0;
        for (int k = lgN; k >= 0; k--) {
            Info s = sum[k][y] - sum[k][x];
            if (!pred(cur + s)) {
                ans += 1 << k;
                cur = cur + s;
                x += cnt[k][N] - cnt[k][x];
                y += cnt[k][N] - cnt[k][y];
            } else {
                x = cnt[k][x];
                y = cnt[k][y];
            }
        }
        return {min(ans, N), cur};
    }
    Info query(int x, int y, int rk) {
        Info ans{};
        for (int k = lgN; k >= 0; k--) {
            if (rk >> k & 1) {
                ans += sum[k][y] - sum[k][x];
                x += cnt[k][N] - cnt[k][x];
                y += cnt[k][N] - cnt[k][y];
            } else {
                x = cnt[k][x];
                y = cnt[k][y];
            }
        }
        return ans;
    }
};

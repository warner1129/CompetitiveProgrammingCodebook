auto cmp2 = [&](int a, int b) -> bool { return P[a][1] < P[b][1]; };
auto cdq = [&](auto self, auto l, auto r) {
    if (r - l == 1) return;
    auto mid = l + (r - l) / 2;
    self(self, l, mid);
    auto tmp = vector<int>(mid, r);
    sort(l, mid, cmp2);
    sort(mid, r, cmp2);
    for (auto i = l, j = mid; j < r; j++) {
        while (i != mid and P[*i][1] < P[*j][1]) {
            bit.add(P[*i][2], dp[*i]);
            i++;
        }
        dp[*j].upd(bit.qry(P[*j][2]));
    };
    for (auto i = l; i < mid; i++) bit.reset(P[*i][2]);
    copy(all(tmp), mid);
    self(self, mid, r);
}; cdq(cdq, all(ord));
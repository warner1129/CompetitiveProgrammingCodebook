vector<pair<int, int>> floor_block(int x) { // x >= 0
    vector<pair<int, int>> itv;
    for (int l = 1, r; l <= x; l = r) {
        r = l + (x % l) / (x / l) + 1;
        itv.emplace_back(l, r);
    }
    return itv;
}
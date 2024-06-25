vector<i64> floorBlock(i64 x) { // x >= 0
    vector<i64> itv;
    for (i64 l = 1, r; l <= x; l = r) {
        r = x / (x / l) + 1;
        itv.push_back(l);
    }
    return itv;
}
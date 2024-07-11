pair<i64, i64> Split(i64 x) {
    if (x == 1) return {0, 0}; 
    i64 h = __lg(x);
    i64 fill = (1LL << (h + 1)) - 1;
    i64 l = (1LL << h) - 1 - max(0LL, fill - x - (1LL << (h - 1)));
    i64 r = x - 1 - l;
    return {l, r};
}
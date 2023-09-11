pair<i64, i64> exgcd(i64 a, i64 b) { // ax + by = 1
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a % b);
    return {y, x - a / b * y};
};
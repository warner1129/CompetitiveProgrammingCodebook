i64 ifloor(i64 a, i64 b) {
    if (b < 0) a = -a, b = -b;
    if (a < 0) return (a - b + 1) / b;
    return a / b;
}

i64 iceil(i64 a, i64 b) {
    if (b < 0) a = -a, b = -b;
    if (a > 0) return (a + b - 1) / b;
    return a / b;
}
i64 next_perm(i64 x) {
    i64 y = x | (x - 1);
    return (y + 1) | (((~y & -~y) - 1) >> (__builtin_ctz(x) + 1));
}
// p[0], p[1], p[2] should be counterclockwise order
int inCC(const array<Pt, 3> &p, Pt a) {
    i128 det = 0;
    for (int i = 0; i < 3; i++)
        det += i128(abs2(p[i]) - abs2(a)) * ori(a, p[(i + 1) % 3], p[(i + 2) % 3]);
    return (det > 0) - (det < 0); // in:1, on:0, out:-1
}

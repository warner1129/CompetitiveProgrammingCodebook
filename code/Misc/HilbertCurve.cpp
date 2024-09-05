i64 hilbert(int n, int x, int y) {
    i64 pos = 0;
    for (int s = (1 << n) / 2; s; s /= 2) {
        int rx = (x & s) > 0;
        int ry = (y & s) > 0;
        pos += 1LL * s * s * ((3 * rx) ^ ry);
        if (ry == 0) {
            if (rx == 1) x = s - 1 - x, y = s - 1 - y;
            swap(x, y);
        }
    }
    return pos;
}
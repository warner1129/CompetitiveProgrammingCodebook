template <class T>
T BSGS(T x, T y, T M) {
  // x^? \equiv y (mod M)
  T t = 1, c = 0, g = 1;
  for (T M_ = M; M_ > 0; M_ >>= 1) g = g * x % M;
  for (g = gcd(g, M); t % g != 0; ++c) {
    if (t == y) return c;
    t = t * x % M;
  }
  if (y % g != 0) return -1;
  t /= g, y /= g, M /= g;
  T h = 0, gs = 1;
  for (; h * h < M; ++h) gs = gs * x % M;
  unordered_map<T, T> bs;
  for (T s = 0; s < h; bs[y] = ++s) y = y * x % M;
  for (T s = 0; s < M; s += h) {
    t = t * gs % M;
    if (bs.count(t)) return c + s + h - bs[t];
  }
  return -1;
}
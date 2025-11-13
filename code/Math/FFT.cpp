using cplx = complex<Real>;
struct FFT {
	static const int Log = 21;
    array<cplx, Log + 1> e{}, ie{};
    FFT() {
        for (int i = Log; i >= 0; i--) {
            e[i] = polar({1}, 2 * pi / (1 << i));
            ie[i] = conj(e[i]);
        }
    }
    void operator()(vector<cplx> &v, bool inv) {
        int n = v.size();
        for (int i = 0, j = 0; i < n; i++) {
            if (i < j) swap(v[i], v[j]);
            for (int k = n / 2; (j ^= k) < k; k /= 2);
        }
        for (int m = 1; m < n; m *= 2) {
            cplx w = (inv ? ie : e)[__lg(m) + 1];
            for (int i = 0; i < n; i += m * 2) {
                cplx cur = 1;
                for (int j = i; j < i + m; j++) {
                    auto g = v[j], t = cur * v[j + m];
                    v[j] = g + t;
                    v[j + m] = g - t;
                    cur = cur * w;
                }
            }
        }
        if (inv) {
            Real in = 1. / n;
            for (int i = 0; i < n; i++) v[i] *= in;
        }
    }
};
Poly operator*(Poly f, const Poly &g) {
    constexpr int M = 1E6;
    int n = ssize(f) + ssize(g) - 1;
    int len = bit_ceil(1ull * n);
    vector<cplx> _f(len), _g(len);
    for (int i = 0; i < len; i++) {
        _f[i] = (i < f.size() ? f[i] : 0);
        _g[i] = (i < g.size() ? g[i] : 0);
    }
    fft(_f, 0), fft(_g, 0);
    for (int i = 0; i < len; i++) _f[i] *= _g[i];
    fft(_f, 1);
    f.resize(n);
    for (int i = 0; i < n; i++) f[i] = round(_f[i].real());
    return f;
}

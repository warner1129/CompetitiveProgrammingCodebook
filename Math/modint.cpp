// 1012924417 -> 5, 924844033 -> 5
// 998244353  -> 3, 897581057 -> 3
// 645922817  -> 3, 167772161 -> 3
template <uint32_t mod> struct modint {
    uint32_t val;
public:
    static modint raw(int v) { modint x; x.val = v; return x; }
    modint() : val(0) {}
    template <class T>
    modint(T v) { int64_t x = (int64_t)(v%(int64_t)(mod)); if (x < 0) x += mod; val = (uint32_t)(x); }
    modint(bool v) { val = ((unsigned int)(v) % mod); }
    modint& operator++() { val++; if (val == mod) val = 0; return *this; }
    modint& operator--() { if (val == 0) val = mod; val--; return *this; }
    modint operator++(int) { modint result = *this; ++*this; return result; }
    modint operator--(int) { modint result = *this; --*this; return result; }
    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= mod) val -= mod; return *this; }
    modint& operator-=(const modint& rhs) { val -= rhs.val; if (val >= mod) val += mod; return *this; }
    modint& operator*=(const modint& rhs) { uint64_t z = val; z *= rhs.val; val = (uint32_t)(z % mod); return *this; }
    modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(mod-2); }
    friend modint operator+(const modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }
    friend modint operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs; }
    friend modint operator*(const modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }
    friend modint operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs; }
    friend bool operator==(const modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }
    friend bool operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val; }
};
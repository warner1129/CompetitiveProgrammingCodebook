// 暴力乘法，只能做到 10^5 位數 
// 只加減不做乘法 Base 可到 1E18
struct uBig {
    static const i64 Base = 1E15;
    static const i64 Log = 15;
    vector<i64> d;
    uBig() : d{0} {}
    uBig(i64 x) {
        d = {x % Base};
        if (x >= Base) {
            d.push_back(x / Base);
        }
        fix();
    }
    uBig(string_view s) {
        i64 c = 0, pw = 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            c += pw * (s[i] - '0');
            pw *= 10;
            if (pw == Base or i == 0) {
                d.push_back(c);
                c = 0;
                pw = 1;
            }
        }
    }
    void fix() {
        i64 c = 0;
        for (int i = 0; i < d.size(); i++) {
            d[i] += c;
            c = (d[i] < 0 ? (d[i] - 1 - Base) / Base : d[i] / Base);
            d[i] -= c * Base;
        }
        while (c) {
            d.push_back(c % Base);
            c /= Base;
        }
        while (d.size() >= 2 and d.back() == 0) {
            d.pop_back();
        }
    }
    bool isZero() const {
        return d.size() == 1 and d[0] == 0;
    }
    uBig &operator+=(const uBig &rhs) {
        if (d.size() < rhs.d.size()) {
            d.resize(rhs.d.size());
        }
        for (int i = 0; i < rhs.d.size(); i++) {
            d[i] += rhs.d[i];
        }
        fix();
        return *this;
    }
    uBig &operator-=(const uBig &rhs) {
        if (d.size() < rhs.d.size()) {
            d.resize(rhs.d.size());
        }
        for (int i = 0; i < rhs.d.size(); i++) {
            d[i] -= rhs.d[i];
        }
        fix();
        return *this;
    }
    friend uBig operator*(const uBig &lhs, const uBig &rhs) {
        const int a = lhs.d.size(), b = rhs.d.size();
        uBig res(0);
        res.d.resize(a + b);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                i128 x = (i128)lhs.d[i] * rhs.d[j];
                res.d[i + j] += x % Base;
                res.d[i + j + 1] += x / Base;
            }
        }
        res.fix();
        return res;
    };
    friend uBig &operator+(uBig lhs, const uBig &rhs) {
        return lhs += rhs;
    }
    friend uBig &operator-(uBig lhs, const uBig &rhs) {
        return lhs -= rhs;
    }
    uBig &operator*=(const uBig &rhs) {
        return *this = *this * rhs;
    }
    friend int cmp(const uBig &lhs, const uBig &rhs) {
        if (lhs.d.size() != rhs.d.size()) {
            return lhs.d.size() < rhs.d.size() ? -1 : 1;
        }
        for (int i = lhs.d.size() - 1; i >= 0; i--) {
            if (lhs.d[i] != rhs.d[i]) {
                return lhs.d[i] < rhs.d[i] ? -1 : 1;
            }
        }
        return 0;
    }
    friend ostream &operator<<(ostream &os, const uBig &rhs) {
        os << rhs.d.back();
        for (int i = ssize(rhs.d) - 2; i >= 0; i--) {
            os << setfill('0') << setw(Log) << rhs.d[i];
        }
        return os;
    }
    friend istream &operator>>(istream &is, uBig &rhs) {
        string s;
        is >> s;
        rhs = uBig(s);
        return is;
    }
};

struct sBig : uBig {
    bool neg{false};
    sBig() : uBig() {}
    sBig(i64 x) : uBig(abs(x)), neg(x < 0) {}
    sBig(string_view s) : uBig(s[0] == '-' ? s.substr(1) : s), neg(s[0] == '-') {}
    sBig(const uBig &x) : uBig(x) {}
    sBig operator-() const {
        if (isZero()) {
            return *this;
        }
        sBig res = *this;
        res.neg ^= 1;
        return res;
    }
    sBig &operator+=(const sBig &rhs) {
        if (rhs.isZero()) {
            return *this;
        }
        if (neg == rhs.neg) {
            uBig::operator+=(rhs);
        } else {
            int s = cmp(*this, rhs);
            if (s == 0) {
                *this = {};
            } else if (s == 1) {
                uBig::operator-=(rhs);
            } else {
                uBig tmp = rhs;
                tmp -= static_cast<uBig>(*this);
                *this = tmp;
                neg = rhs.neg;
            }
        }
        return *this;
    }
    sBig &operator-=(const sBig &rhs) {
        neg ^= 1;
        *this += rhs;
        neg ^= 1;
        if (isZero()) {
            neg = false;
        }
        return *this;
    }
    sBig &operator*=(const sBig &rhs) {
        if (isZero() or rhs.isZero()) {
            return *this = {};
        }
        neg ^= rhs.neg;
        uBig::operator*=(rhs);
        return *this;
    }
    friend sBig operator+(sBig lhs, const sBig &rhs) {
        return lhs += rhs;
    }
    friend sBig &operator-(sBig lhs, const sBig &rhs) {
        return lhs -= rhs;
    }
    friend sBig operator*(sBig lhs, const sBig &rhs) {
        return lhs *= rhs;
    }
    friend ostream &operator<<(ostream &os, const sBig &rhs) {
        if (rhs.neg) {
            os << '-';
        }
        return os << static_cast<uBig>(rhs);
    }
    friend istream &operator>>(istream &is, sBig &rhs) {
        string s;
        is >> s;
        rhs = sBig(s);
        return is;
    }
};

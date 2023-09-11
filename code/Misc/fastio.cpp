struct FastIO {
    const static int ibufsiz = 4<<20, obufsiz = 18<<20;
    char ibuf[ibufsiz], *ipos = ibuf, obuf[obufsiz], *opos = obuf;
    FastIO() { fread(ibuf, 1, ibufsiz, stdin); }
    ~FastIO() { fwrite(obuf, 1, opos - obuf, stdout); }
    template<class T> FastIO& operator>>(T &x) {
        bool sign = 0; while (!isdigit(*ipos)) { if (*ipos == '-') sign = 1; ++ipos; } 
        x = *ipos++ & 15;
        while (isdigit(*ipos)) x = x * 10 + (*ipos++ & 15);
        if (sign) x = -x;
        return *this;
    }
    template<class T> FastIO& operator<<(T n) {
        static char _buf[18];
        char* _pos = _buf;
        if (n < 0) *opos++ = '-', n = -n;
        do *_pos++ = '0' + n % 10; while (n /= 10);
        while (_pos != _buf) *opos++ = *--_pos;
        return *this;
    }
    FastIO& operator<<(char ch) { *opos++ = ch; return *this; }
} FIO;
#define cin FIO
#define cout FIO
namespace sfx {
#define fup(a, b) for (int i = a; i < b; i++) 
#define fdn(a, b) for (int i = b - 1; i >= a; i--)
    constexpr int N = 5e5 + 5;
    bool _t[N * 2];
    int H[N], RA[N], x[N], _p[N];
    int SA[N * 2], _s[N * 2], _c[N * 2], _q[N * 2];
    void pre(int *sa, int *c, int n, int z) {
        fill_n(sa, n, 0), copy_n(c, z, x);
    }
    void induce(int *sa, int *c, int *s, bool *t, int n, int z) {
        copy_n(c, z - 1, x + 1);
        fup(0, n) if (sa[i] and !t[sa[i] - 1])
            sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
        copy_n(c, z, x);
        fdn(0, n) if (sa[i] and t[sa[i] - 1])
            sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
    }
    void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
        bool uniq = t[n - 1] = true;
        int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
        fill_n(c, z, 0);
        fup(0, n) uniq &= ++c[s[i]] < 2;
        partial_sum(c, c + z, c);
        if (uniq) { fup(0, n) sa[--c[s[i]]] = i; return; }
        fdn(0, n - 1)
            t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
        pre(sa, c, n, z);
        fup(1, n) if (t[i] and !t[i - 1])
            sa[--x[s[i]]] = p[q[i] = nn++] = i;
        induce(sa, c, s, t, n, z);
        fup(0, n) if (sa[i] and t[sa[i]] and !t[sa[i] - 1]) {
            bool neq = last < 0 or !equal(s + sa[i], s + p[q[sa[i]] + 1], s + last);
            ns[q[last = sa[i]]] = nmxz += neq;
        }
        sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
        pre(sa, c, n, z);
        fdn(0, nn) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
        induce(sa, c, s, t, n, z);
    }
    vector<int> build(vector<int> s, int n) {
        copy_n(begin(s), n, _s), _s[n] = 0;
        sais(_s, SA, _p, _q, _t, _c, n + 1, 256);
        vector<int> sa(n);
        fup(0, n) sa[i] = SA[i + 1];
        return sa;
    }
    vector<int> lcp_array(vector<int> &s, vector<int> &sa) {
        int n = int(s.size());
        vector<int> rnk(n);
        fup(0, n) rnk[sa[i]] = i;
        vector<int> lcp(n - 1);
        int h = 0;
        fup(0, n) {
            if (h > 0) h--;
            if (rnk[i] == 0) continue;
            int j = sa[rnk[i] - 1];
            for (; j + h < n and i + h < n; h++)
                if (s[j + h] != s[i + h]) break;
            lcp[rnk[i] - 1] = h;
        }
        return lcp;
    }
}

struct SAM {
    vector<array<int, 26>> nxt;
    vector<int> fail, len;
    int lst = 0;
    int newNode() {
        fail.push_back(0);
        len.push_back(0);
        nxt.push_back({});
        return fail.size() - 1;
    }
    SAM() : lst(newNode()) {}
    void reset() { lst = 0; } /* SPLIT-HASH */
    int add(int c) {
        if (nxt[lst][c] and len[nxt[lst][c]] == len[lst] + 1) { // 廣義
            return lst = nxt[lst][c];
        }
        int cur = newNode();
        len[cur] = len[lst] + 1;
        while (lst and nxt[lst][c] == 0) {
            nxt[lst][c] = cur;
            lst = fail[lst];
        } /* SPLIT-HASH */
        int p = nxt[lst][c];
        if (p == 0) {
            fail[cur] = 0;
            nxt[0][c] = cur;
        } else if (len[p] == len[lst] + 1) {
            fail[cur] = p;
        } else {
            int t = newNode();
            nxt[t] = nxt[p];
            fail[t] = fail[p];
            len[t] = len[lst] + 1;
            while (nxt[lst][c] == p) {
                nxt[lst][c] = t;
                lst = fail[lst];
            }
            fail[p] = fail[cur] = t;
        }
        return lst = cur;
    } /* SPLIT-HASH */
    vector<int> order() { // 長度遞減
        vector<int> cnt(len.size());
        for (int i = 0; i < len.size(); i++)
            cnt[len[i]]++;
        partial_sum(rall(cnt), cnt.rbegin());
        vector<int> ord(cnt[0]);
        for (int i = len.size() - 1; i >= 0; i--)
            ord[--cnt[len[i]]] = i;
        return ord;
    }
};

struct SAM {
    struct Node {
        int link{}, len{};
        array<int, 26> ch{};
    };
    vector<Node> n;
    int lst = 0;
    SAM() : n(1) {}
    int newNode() {
        n.emplace_back();
        return n.size() - 1;
    }
    void reset() {
        lst = 0;
    }
    int add(int c) {
        if (n[lst].ch[c] != 0 and n[n[lst].ch[c]].len == n[lst].len + 1) { // General
            return lst = n[lst].ch[c];
        }
        int cur = newNode();
        n[cur].len = n[lst].len + 1;
        while (lst != 0 and n[lst].ch[c] == 0) {
            n[lst].ch[c] = cur;
            lst = n[lst].link;
        }
        int p = n[lst].ch[c];
        if (p == 0) {
            n[cur].link = 0;
            n[0].ch[c] = cur;
        } else if (n[p].len == n[lst].len + 1) {
            n[cur].link = p;
        } else {
            int t = newNode();
            n[t] = n[p];
            n[t].len = n[lst].len + 1;
            while (n[lst].ch[c] == p) {
                n[lst].ch[c] = t;
                lst = n[lst].link;
            }
            n[p].link = n[cur].link = t;
        }
        return lst = cur;
    }
};
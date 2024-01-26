struct SAM {
    struct Node {
        int link{}, len{};
        i64 cnt{};
        array<int, 26> ch{};
    };
    vector<Node> n;
    vector<int> E;
    const int root = 0;
    int lst = 0;
    SAM() : n(1) {}
    SAM(string_view s) : SAM{} {
        for (char c : s) {
            add(c - 'a');
        }
    }
    int newNode() {
        n.emplace_back();
        return n.size() - 1;
    }
    void add(int c) {
        int cur = newNode();
        E.push_back(cur);
        n[cur].len = n[lst].len + 1;
        while (lst != root and n[lst].ch[c] == root) {
            n[lst].ch[c] = cur;
            lst = n[lst].link;
        }
        int p = n[lst].ch[c];
        if (p == 0) {
            n[cur].link = root;
            n[root].ch[c] = cur;
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
        lst = cur;
    }
};
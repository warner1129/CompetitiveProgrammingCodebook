struct PAM {
    struct Node {
        int fail, len, dep;
        array<int, 26> ch;
        Node(int _len) : len{_len}, fail{}, ch{}, dep{} {};
    };
    vector<Node> g;
    vector<int> id;
    int odd, even, lst;
    string S;
    int new_node(int len) {
        g.emplace_back(len);
        return g.size() - 1;
    }
    PAM() : odd(new_node(-1)), even(new_node(0)) {
        lst = g[even].fail = odd;
    }
    int up(int p) {
        while (S.rbegin()[g[p].len + 1] != S.back())
            p = g[p].fail;
        return p;
    }
    int add(char c) {
        S += c;	
        lst = up(lst);
        c -= 'a';
        if (!g[lst].ch[c]) g[lst].ch[c] = new_node(g[lst].len + 2);
        int p = g[lst].ch[c];
        g[p].fail = (lst == odd ? even : g[up(g[lst].fail)].ch[c]);
        lst = p;
        g[lst].dep = g[g[lst].fail].dep + 1;
        id.push_back(lst);
        return lst;
    }
    void del() {
        S.pop_back();
        id.pop_back();
        lst = id.empty() ? odd : id.back();
    }
};

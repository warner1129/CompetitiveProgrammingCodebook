struct Node {
    Node *ch[2]{};
    Node *fail{};
    bool ed{};
} pool[(i64)1E6]{};
int top = 0;
Node *newNode() {
    auto p = &pool[top++];
    p->ch[0] = p->ch[1] = {};
    p->fail = {};
    p->ed = {};
    return p;
}
struct ACauto {
    Node *root;
    ACauto() {
        top = 0;
        root = newNode();
    }
    void add(string_view s) {
        auto p = root;
        for (char c : s) {
            c -= '0';
            if (!p->ch[c]) {
                p->ch[c] = newNode();
            }
            p = p->ch[c];
        }
        p->ed = true;
    }
    void build() {
        queue<Node*> que;
        root->fail = root;
        for (auto &p : root->ch) {
            if (p) {
                que.push(p);
                p->fail = root;
            } else {
                p = root;
            }
        }
        while (!que.empty()) {
            auto u = que.front();
            que.pop();
            for (int i : {0, 1}) {
                if (u->ch[i]) {
                    u->ch[i]->fail = u->fail->ch[i];
                    que.push(u->ch[i]);
                } else {
                    u->ch[i] = u->fail->ch[i];
                }
            }
        }
    }
};
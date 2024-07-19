const int sigma = ;

struct Node {
    Node *ch[sigma]{};
    Node *fail{}, *next{};
    bool end{};
} pool[i64(1E6)]{};

struct ACauto {
    int top;
    Node *root;
    ACauto() {
        top = 0;
        root = new (pool + top++) Node();
    }
    int add(string_view s) {
        auto p = root;
        for (char c : s) {
            c -= ;
            if (!p->ch[c]) {
                p->ch[c] = new (pool + top++) Node();
            }
            p = p->ch[c];
        }
        p->end = true;
        return p - pool;
    }
    vector<Node*> ord;
    void build() {
        queue<Node*> que;
        root->fail = root;
        for (auto &p : root->ch) {
            if (p) {
                p->fail = root;
                que.push(p);
            } else {
                p = root;
            }
        }
        while (!que.empty()) {
            auto p = que.front();
            que.pop();
            ord.push_back(p);
            p->next = (p->fail->end ? p->fail : p->fail->next);
            for (int i = 0; i < sigma; i++) {
                if (p->ch[i]) {
                    p->ch[i]->fail = p->fail->ch[i];
                    que.push(p->ch[i]);
                } else {
                    p->ch[i] = p->fail->ch[i];
                }
            }
        }
    }
};
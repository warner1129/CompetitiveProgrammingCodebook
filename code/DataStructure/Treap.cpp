struct Node {
    Node *ls{}, *rs{};
    u32 w{};
    Info info{}, sum{};
    Tag tag{};
    Node() {};
    Node(Info x) : ls{}, rs{}, 
        w(rng()), info(x), sum(x) {}
    void apply(const Tag &t) {
        t(info), t(sum), t(tag);
    }
    void push() {
        if (ls) ls->apply(tag);
        if (rs) rs->apply(tag);
        tag = {};
    }
    void pull() {
        sum = info;
        if (ls) sum = ls->sum + sum;
        if (rs) sum = sum + rs->sum;
    }
}; /* SPLIT-HASH */
Info get(Node *p) { return p ? p->sum : Info{}; }
pair<Node*, Node*> split(Node *t, auto &&pred, Info cur = {}) {
    if (!t) return {{}, {}};
    t->push();
    Info ncur = cur + get(t->ls) + t->info;
    if (pred(ncur)) {
        auto [x, y] = split(t->rs, pred, ncur);
        t->rs = x;
        t->pull();
        return {t, y};
    } else {
        auto [x, y] = split(t->ls, pred, cur);
        t->ls = y;
        t->pull();
        return {x, t};
    }
} /* SPLIT-HASH */
Node* merge(Node *a, Node *b) {
    if (!a or !b) return a ? a : b;
    if (a->w < b->w) {
        a->push();
        a->rs = merge(a->rs, b);
        a->pull();
        return a;
    } else {
        b->push();
        b->ls = merge(a, b->ls);
        b->pull();
        return b;
    }
} /* SPLIT-HASH */
Node* join(Node *a, Node *b) {
    if (!a or !b) return a ? a : b;
    if (a->w > b->w) swap(a, b);
    Info m = a->info;
    auto [x, y] = split(b, [=](const Info &p) {
        return p < m ? true : m < p ? false : rng() % 2;
    });
    a->push();
    a->ls = join(a->ls, x);
    a->rs = join(a->rs, y);
    a->pull();
    return a;
}

struct Node {
    Node *ch[2]{}, *p{};
    Info info{}, sum{};
    Tag tag{};
    int size{};
    bool rev{};
} pool[int(1E5 + 10)], *top = pool;
Node *newNode(Info a) {
    Node *t = top++;
    t->info = t->sum = a;
    t->size = 1;
    return t;
}
int size(const Node *x) { return x ? x->size : 0; }
Info get(const Node *x) { return x ? x->sum : Info{}; }
int dir(const Node *x) { return x->p->ch[1] == x; }
bool nroot(const Node *x) { return x->p and x->p->ch[dir(x)] == x; }
void reverse(Node *x) { if (x) x->rev = !x->rev; }
void update(Node *x, const Tag &f) {
    if (!x) return;
    f(x->tag);
    f(x->info);
    f(x->sum);
}
void push(Node *x) {
    if (x->rev) {
        swap(x->ch[0], x->ch[1]);
        reverse(x->ch[0]);
        reverse(x->ch[1]);
        x->rev = false;
    }
    update(x->ch[0], x->tag);
    update(x->ch[1], x->tag);
    x->tag = Tag{};
}
void pull(Node *x) {
    x->size = size(x->ch[0]) + 1 + size(x->ch[1]);
    x->sum = get(x->ch[0]) + x->info + get(x->ch[1]);
} /* SPLIT-HASH */
void rotate(Node *x) {
    Node *y = x->p, *z = y->p;
    push(y);
    int d = dir(x);
    push(x);
    Node *w = x->ch[d ^ 1];
    if (nroot(y)) {
        z->ch[dir(y)] = x;
    }
    if (w) {
        w->p = y;
    }
    (x->ch[d ^ 1] = y)->ch[d] = w;
    (y->p = x)->p = z;
    pull(y);
    pull(x);
}
void splay(Node *x) {
    while (nroot(x)) {
        Node *y = x->p;
        if (nroot(y)) {
            rotate(dir(x) == dir(y) ? y : x);
        }
        rotate(x);
    }
}
Node *nth(Node *x, int k) {
    assert(size(x) > k);
    while (true) {
        push(x);
        int left = size(x->ch[0]);
        if (left > k) {
            x = x->ch[0];
        } else if (left < k) {
            k -= left + 1;
            x = x->ch[1];
        } else {
            break;
        }
    }
    splay(x);
    return x;
} /* SPLIT-HASH */
Node *split(Node *x) {
    assert(x);
    push(x);
    Node *l = x->ch[0];
    if (l) l->p = x->ch[0] = nullptr;
    pull(x);
    return l;
}
Node *join(Node *x, Node *y) {
    if (!x or !y) return x ? x : y;
    y = nth(y, 0);
    push(y);
    y->ch[0] = x;
    if (x) x->p = y;
    pull(y);
    return y;
}
Node *find_first(Node *x, auto &&pred) {
    Info pre{};
    while (true) {
        push(x);
        if (pred(pre + get(x->ch[0]))) {
            x = x->ch[0];
        } else if (pred(pre + get(x->ch[0]) + x->info) or !x->ch[1]) {
            break;
        } else {
            pre = pre + get(x->ch[0]) + x->info;
            x = x->ch[1];
        }
    }
    splay(x);
    return x;
}

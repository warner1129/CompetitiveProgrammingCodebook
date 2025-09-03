namespace lct {
Node *access(Node *x) {
    Node *last = {};
    while (x) {
        splay(x);
        push(x);
        x->ch[0] = last;
        pull(x);
        last = x;
        x = x->p;
    }
    return last;
}
void make_root(Node *x) {
    access(x);
    splay(x);
    reverse(x);
}
Node *find_root(Node *x) {
    push(x = access(x));
    while (x->ch[1]) {
        push(x = x->ch[1]);
    }
    splay(x);
    return x;
} /* SPLIT-HASH */
bool link(Node *x, Node *y) {
    if (find_root(x) == find_root(y)) {
        return false;
    }
    make_root(x);
    x->p = y;
    return true;
}
bool cut(Node *a, Node *b) {
    make_root(a);
    access(b);
    splay(a);
    if (a->ch[0] == b) {
        split(a);
        return true;
    }
    return false;
}
Info query(Node *a, Node *b) {
    make_root(b);
    return get(access(a));
}
void set(Node *x, Info v) {
    splay(x);
    push(x);
    x->info = v;
    pull(x);
} }

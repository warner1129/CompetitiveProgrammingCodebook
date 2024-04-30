mt19937 rng(random_device{}());
template<class S, class T>
struct Treap {
    struct Node {
        Node *ls{}, *rs{};
        int pos, siz;
        u32 pri;
        S d{}, e{};
        T f{};
        Node(int p, S x) : d{x}, e{x}, pos{p}, siz{1}, pri{rng()} {}
        void upd(T &g) {
            g(d), g(e), g(f);
        }
        void pull() {
            siz = Siz(ls) + Siz(rs);
            d = Get(ls) + e + Get(rs);
        }
        void push() {
            if (ls) ls->upd(f);
            if (rs) rs->upd(f);
            f = T{};
        }
    } *root{};
    static int Siz(Node *p) { return p ? p->siz : 0; }
    static S Get(Node *p) { return p ? p->d : S{}; }
    Treap() : root{} {}
    Node* Merge(Node *a, Node *b) {
        if (!a or !b) return a ? a : b;
        if (a->pri < b->pri) {
            a->push();
            a->rs = Merge(a->rs, b);
            a->pull();
            return a;
        } else {
            b->push();
            b->ls = Merge(a, b->ls);
            b->pull();
            return b;
        }
    }
    void Split(Node *p, Node *&a, Node *&b, int k) {
        if (!p) return void(a = b = nullptr);
        p->push();
        if (p->pos <= k) {
            a = p;
            Split(p->rs, a->rs, b, k);
            a->pull();
        } else {
            b = p;
            Split(p->ls, a, b->ls, k);
            b->pull();
        }
    }
    void insert(int p, S x) {
        Node *L, *R;
        Split(root, L, R, p);
        root = Merge(Merge(L, new Node(p, x)), R);
    }
    void erase(int x) {
        Node *L, *M, *R;
        Split(root, M, R, x);
        Split(M, L, M, x - 1);
        if (M) M = Merge(M->ls, M->rs);
        root = Merge(Merge(L, M), R);
    }
    S query() {
        return Get(root);
    }
};
struct ACauto {
	static const int sigma = 26;
	struct Node {
		array<Node*, sigma> ch{};
		Node *fail = nullptr;
		int cnt = 0;
		vector<int> id;
	} *root;
	ACauto() : root(new Node()) {}
	void insert(const string &s, int id) {
		auto p = root;
		for (char c : s) {
			int d = c - 'a';
			if (!p->ch[d]) p->ch[d] = new Node();
			p = p->ch[d];
		}
		p->id.emplace_back(id);
	}
	vector<Node*> ord;
	void build() {
		root->fail = root;
		queue<Node*> que;
		for (int i = 0; i < sigma; i++) {
			if (root->ch[i]) {
				root->ch[i]->fail = root;
				que.emplace(root->ch[i]);
			}
			else {
				root->ch[i] = root;
			}
		}
		while (!que.empty()) {
			auto p = que.front(); que.pop();
			ord.emplace_back(p);
			for (int i = 0; i < sigma; i++) {
				if (p->ch[i]) {
					p->ch[i]->fail = p->fail->ch[i];
					que.emplace(p->ch[i]);
				}
				else {
					p->ch[i] = p->fail->ch[i];
				}
			}
		}
	}
	void walk(const string &s) {
		auto p = root;	
		for (const char &c : s) {
			int d = c - 'a';
			(p = p->ch[d])->cnt++;
		}
	}
	void count(vector<int> &cnt) {
		reverse(all(ord));
		for (auto p : ord) {
			p->fail->cnt += p->cnt;
			for (int id : p->id)
				cnt[id] = p->cnt;
		}
	}
};
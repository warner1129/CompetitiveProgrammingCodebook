struct HopcroftKarp {
	vector<vector<int>> G;
	vector<int> l, r;
	int n, m;
	HopcroftKarp(int n, int m) : n(n), m(m), l(n, -1), r(m, -1), G(n) {}
	void add_edge(int u, int v) {
		G[u].emplace_back(v);
	}
	vector<int> dep;
	bool bfs() {
		dep.assign(n, 0);
		queue<int> que;
		for (int i = 0; i < n; i++)
			if (l[i] == -1) que.emplace(i), dep[i] = 1;
		int q = INF;
		while (!que.empty()) {
			int u = que.front(); que.pop();
			if (dep[u] > q) break;
			for (int v : G[u]) {
				if (r[v] == -1) q = dep[u];
				else if (r[v] != u and !dep[r[v]])
					que.emplace(r[v]), dep[r[v]] = dep[u]+1;
			}
		}
		return q != INF;
	}
	bool dfs(int u) {
		for (int v : G[u])
			if (r[v] == -1 or (dep[r[v]] == dep[u]+1 and dfs(r[v])))
				return l[u] = v, r[v] = u, dep[u] = 0, true;
		dep[u] = 0;
		return false;
	}
	int max_match() {
		int ans = 0;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				if (dep[i] == 1) ans += dfs(i);
		}
		return ans;
	}
};


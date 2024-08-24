#include <bits/stdc++.h>

using namespace std;

#define int long long

template<typename T>
void read(T &x) {
	x = 0; char ch = getchar(); int f = 0;
	for (; !isdigit(ch); ch = getchar()) f |= (ch == '-');
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	x = f ? ~x + 1 : x;
}

template<typename T, typename ...Args>
void read(T &x, Args &...args) {
	read(x); read(args...);
}

#define mp make_pair

constexpr int N = 1e4 + 5, M = 1e2 + 5;

int n, m, k, s, t, u, v, w;
int dis[N][M]; bool vis[N][M];
vector<pair<int, int> > G[N];

struct node{
	int id, dep, dis;

	node(): id(0), dep(0), dis(0) {}
	node(int x, int y, int z): id(x), dep(y), dis(z) {}
	friend bool operator < (const node a, const node b) {
		return a.dis > b.dis;
	}
};

priority_queue<node> Q;


void dijkstra(int s, int t) {
	memset(dis, 0x3f, sizeof dis);
	Q.push(node(s, 0, 0)); dis[s][0] = 0;
	while (Q.size()) {
		node u = Q.top(); Q.pop();
		int kk = u.dep;
		if (vis[u.id][kk]) continue;
		vis[u.id][kk] = true;
		for (auto v : G[u.id]) {
			int y = v.first;
			if (kk < k && dis[y][kk + 1] > dis[u.id][kk]) {
				dis[y][kk + 1] = dis[u.id][kk];
				Q.push(node(y, kk + 1, dis[y][kk + 1]));
			}
			if (dis[y][kk] > dis[u.id][kk] + v.second) {
				dis[y][kk] = dis[u.id][kk] + v.second;
				Q.push(node(y, kk, dis[y][kk]));
			}
		}
	}
}

signed main() {
	read(n), read(m), read(k), read(s), read(t); ++ s, ++ t;
	for (int i = 1; i <= m; ++i) {
		read(u, v, w); ++ u, ++ v;
		G[u].emplace_back(mp(v, w));
		G[v].emplace_back(mp(u, w));
	} dijkstra(s, t);
	int ans = 2147483647;
	for (int i = 0; i <= k; ++i) ans = min(ans, dis[t][i]);
	return printf("%lld\n", ans), 0;
}
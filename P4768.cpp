#include <bits/stdc++.h>
#define int long long
using pii = std::pair<int, int>;
const int N = 4e5 + 5, M = N << 1, K = 32;
int n, m, q, k, s, cnt, fa[N], anc[N][K], head[N], to[M], next[M], link[M], dis[N], height[N];
bool vis[N];
struct edge {int u, v, h; bool operator < (const edge &a) {return h > a.h;}} e[M];
void add(int u, int v, int w) {to[++ cnt] = v, next[cnt] = head[u], link[cnt] = w, head[u] = cnt;}
int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
void dijkstra(int s) {
    std::memset(dis, 0x7f, sizeof dis);
    std::memset(vis, 0, sizeof vis);
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    q.emplace(pii(dis[s] = 0, s));
    while (q.size()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue; vis[u] = true;
        for (int i = head[u]; i; i = next[i]) {
            int v = to[i];
            if (dis[v] > dis[u] + link[i]) {
                dis[v] = dis[u] + link[i];
                if (!vis[v]) q.emplace(pii(dis[v], v));
            }
        }
    } return void();
}
void Exkruscal() {
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= n * 2; ++i) fa[i] = i;
    int id = n;
    for (int i = 1; i <= m; ++i) {
        int fx = find(e[i].u), fy = find(e[i].v);
        if (fx == fy) continue;
        fa[fx] = fa[fy] = ++ id;
        height[id] = e[i].h;
        dis[id] = std::min(dis[fx], dis[fy]);
        anc[fx][0] = anc[fy][0] = id;
    }
    for (int j = 1; j < 32; ++j) for (int i = 1; i <= id; ++i) anc[i][j] = anc[anc[i][j - 1]][j - 1];
}
int Query(int x, int p) {
    for (int i = 31; ~i; --i) if (anc[x][i] && height[anc[x][i]] > p) x = anc[x][i];
    return dis[x];
}
signed main() {
    int T; scanf("%lld", &T);
    while (T--) {
        cnt = 0; std::memset(head, 0, sizeof head);
        scanf("%lld%lld", &n, &m);
        for (int i = 1, u, v, w, h; i <= m; ++i) {
            scanf("%lld%lld%lld%lld", &u, &v, &w, &h);
            add(u, v, w); add(v, u, w);
            e[i] = (edge){u, v, h};
        } dijkstra(1); Exkruscal();
        int lastans = 0;
        scanf("%lld%lld%lld", &q, &k, &s);
        while (q--) {
        	int v, p;
            scanf("%lld%lld", &v, &p);
            v = (v + k * lastans - 1) % n + 1;
            p = (p + k * lastans) % (s + 1);
            printf("%lld\n", lastans = Query(v, p));
        }
    } return 0;
}
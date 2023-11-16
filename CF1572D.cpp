#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()
FILE *fin, *fout, *ferr;
i32 read() {
  i32 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_CF1572D {
  bool _1;
  i32 n, k, tot;
  i32 a[1 << 20], vis[1 << 20];
  i32 cnt[1 << 20];
  struct Edge { i32 u, v, w; } e[(1 << 20) * 20];
  struct MincostMaxflow {
    static const i32 N = (1 << 20) + 5, E = N * 2 + 5;
    static const i64 inf = 0x3f3f3f3f3f3f3f3f;
    i32 s, t, V, cnt = -1;
    i64 dist[N], flow[E << 1];
    i32 head[N];
    bool vis[N];
    class edge {
    public:
      i32 to, f, cost, next;
      edge(i32 to = 0, i64 f = 0, i64 cost = 0, i32 next = 0) : to(to), f(f), cost(cost), next(next) {}
    } e[E << 1];
    void init(i32 _S, i32 _T, i32 _n) {
      std::memset(head, -1, sizeof head);
      s = _S, t = _T, V = _n;
      cnt = -1;
      return void();
    }
    void add_edge(i32 u, i32 v, i64 f, i64 c) {
      e[++cnt] = edge(v, f, c, head[u]);
      head[u] = cnt;
      e[++cnt] = edge(u, 0, -c, head[v]);
      head[v] = cnt;
    }
    bool spfa() {
      for (i32 i = 0; i <= V; ++i) dist[i] = inf, vis[i] = false;
      std::queue<i32> q;
      dist[t] = 0, vis[t] = 1;
      q.emplace(t);
      while (q.size()) {
        i32 x = q.front();
        q.pop();
        vis[x] = false;
        for (i32 i = head[x]; ~i; i = e[i].next)
          if (e[i ^ 1].f > flow[i ^ 1] && dist[e[i].to] > dist[x] - e[i].cost) {
            dist[e[i].to] = dist[x] - e[i].cost;
            if (!vis[e[i].to]) vis[e[i].to] = true, q.emplace(e[i].to);
          }
      }
      return dist[s] < inf;
    }
    i64 dfs(i32 x, i64 cf, i64 &cost) {
      vis[x] = true;
      if (x == t || !cf) return cf;
      i64 getf = 0;
      for (i32 i = head[x]; ~i; i = e[i].next)
        if (!vis[e[i].to] && e[i].f > flow[i] && dist[e[i].to] == dist[x] - e[i].cost) {
          i64 nf = dfs(e[i].to, std::min(cf, e[i].f - flow[i]), cost);
          if (nf) {
            flow[i] += nf, flow[i ^ 1] -= nf;
            getf += nf, cf -= nf;
            cost += nf * e[i].cost;
            if (!cf) break;
          }
        }
      return getf;
    }
    void mcmf(i64 &cost, i64 &flow) {
      cost = flow = 0;
      while (spfa()) {
        vis[t] = true;
        while (vis[t]) {
          std::memset(vis, 0, (V + 1) * sizeof(bool));
          flow += dfs(s, inf, cost);
        }
      }
    }
  } dinic;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), k = read();
    i32 R = (1 << n) - 1;
    cnt[0] = 0;
    for (i32 i = 1; i <= R; ++i) cnt[i] = cnt[i ^ (i & -i)] + 1;
    for (i32 i = 0; i <= R; ++i) a[i] = read();
    for (i32 i = 0; i <= R; ++i)
      for (i32 j = 0; j < n; ++j)
        if (i >> j & 1) e[++tot] = { i, i ^ (1 << j), a[i] + a[i ^ (1 << j)] };
    std::nth_element(e + 1, e + std::min(k * (2 * n - 1), tot), e + tot + 1, [&](const Edge &a, const Edge &b) { return a.w > b.w; });
    dinic.init(R + 1, R + 3, R + 3);
    dinic.add_edge(R + 1, R + 2, k, 0);
    for (i32 i = 1; i <= std::min(tot, k * (2 * n - 1)); ++i) {
      auto& [u, v, w] = e[i];
      if (cnt[u] & 1) dinic.add_edge(u, v, 1, -w);
      else dinic.add_edge(v, u, 1, -w);
      if (!vis[u]) {
        if (cnt[u] & 1) dinic.add_edge(R + 2, u, 1, 0);
        else dinic.add_edge(u, R + 3, 1, 0);
        vis[u] = true;
      }
      if (!vis[v]) {
        if (cnt[v] & 1) dinic.add_edge(R + 2, v, 1, 0);
        else dinic.add_edge(v, R + 3, 1, 0);
        vis[v] = true;
      }
    }
    i64 cost, flow;
    dinic.mcmf(cost, flow);
    fprintf(fout, "%lld\n", -cost);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1572D::main(), 0; }
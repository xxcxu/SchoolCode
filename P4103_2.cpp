#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
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
namespace Solution_Of_P4103 {
  bool _1;
  static const i32 N = 1000005;
  i32 n, m, q;
  i32 dep[N], vis[N], anc[N][22];
  i32 dfn[N], tim = 0;
  i32 st[N], top = 0;
  std::vector<i32> e[N], g[N];
  std::vector<i32> p, vec;
  i64 dp[N][3], depth[N][3], size[N];
  // sum / max / min
  bool _2;
  void add(i32 x, i32 y) {
    g[x].eb(y), g[y].eb(x);
    return void();
  }
  void dfs(i32 x, i32 f) {
    dfn[x] = ++tim;
    anc[x][0] = f;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (i32 &y : e[x])
      if (y != f) {
        dep[y] = dep[x] + 1;
        dfs(y, x);
      }
    return void();
  }
  i32 lca(i32 x, i32 y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 21; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 21; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  void dfs2(i32 x, i32 f) {
    static const i64 INF = 0x3f3f3f3f3f3f3f;
    i64 max = -INF, minimax = -INF;
    i64 min = INF, minimin = INF;
    dp[x][0] = depth[x][0] = size[x] = 0;
    depth[x][1] = dp[x][1] = max, depth[x][2] = dp[x][2] = min;
    for (i32 y : g[x])
      if (y != f) {
        dfs2(y, x);
        size[x] += size[y];
        depth[x][0] += depth[y][0];
        depth[x][1] = std::max(depth[x][1], depth[y][1]);
        depth[x][2] = std::min(depth[x][2], depth[y][2]);
        dp[x][0] += dp[y][0];
        if (depth[y][1] > max) minimax = max, max = depth[y][1];
        else minimax = std::max(minimax, depth[y][1]);
        if (depth[y][2] < min) minimin = min, min = depth[y][2];
        else minimin = std::min(minimin, depth[y][2]);
        dp[x][1] = std::max(dp[x][1], dp[y][1]);
        dp[x][2] = std::min(dp[x][2], dp[y][2]);
      }
    if (minimax != -INF) dp[x][1] = std::max(max + minimax - (i64)2 * dep[x], dp[x][1]);
    if (minimin != INF) dp[x][2] = std::min(min + minimin - (i64)2 * dep[x], dp[x][2]);
    i64 s = 0;
    for (i32 y : g[x])
      if (y != f) {
      dp[x][0] += (i64)1 * (size[x] - size[y]) * depth[y][0];
        s += (i64)1 * (size[x] - size[y]) * size[y];
    }
    dp[x][0] -= (i64)1 * dep[x] * s;
    if (vis[x]) {
      dp[x][0] += depth[x][0] - (i64)1 * dep[x] * size[x];
      dp[x][1] = std::max(dp[x][1], depth[x][1] - dep[x]);
      dp[x][2] = std::min(dp[x][2], depth[x][2] - dep[x]);
      depth[x][0] += dep[x];
      depth[x][1] = std::max(depth[x][1], (i64)dep[x]);
      depth[x][2] = std::min(depth[x][2], (i64)dep[x]);
      ++size[x];
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 1);
    q = read();
    while (q--) {
      m = read();
      p.clear(), vec.clear();
      for (i32 i = 1; i <= m; ++i) p.eb(read());
      std::sort(all(p), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
      for (i32 &v : p) vec.eb(v), vis[v] = true;
      st[top = 1] = 1;
      for (i32 &v : p)
        if (v != 1) {
          i32 L = lca(st[top], v);
          if (L != st[top]) {
            while (dfn[L] < dfn[st[top - 1]]) {
              add(st[top], st[top - 1]);
              --top;
            }
            if (dfn[L] > dfn[st[top - 1]]) {
              vec.eb(L);
              add(L, st[top]);
              st[top] = L;
            } else {
              add(L, st[top--]);
            }
          }
          st[++top] = v;
        }
      vec.eb(1);
      for (i32 i = 1; i < top; ++i) add(st[i], st[i + 1]);
      dfs2(1, 1);
      fprintf(fout, "%lld %lld %lld\n", dp[1][0], dp[1][2], dp[1][1]);
      for (i32 &v : p) vis[v] = false;
      for (i32 &v : vec) g[v].clear();
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P4103::main(), 0; }

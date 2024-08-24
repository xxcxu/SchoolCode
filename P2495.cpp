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
namespace Solution_Of_P2495 {
  bool _1;
  static const i32 N = 500005;
  i32 n, m, q;
  i32 dfn[N], tim = 0;
  i32 st[N], top = 0;
  i32 dep[N], anc[N][22];
  i64 dp[N], min[N];
  std::vector<i32> p, vec, g[N];
  std::vector<std::pair<i32, i32>> e[N];
  bool vis[N];
  bool _2;
  void dfs(i32 x, i32 f) {
    dfn[x] = ++tim;
    anc[x][0] = f;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &[y, z] : e[x])
      if (y != f) {
        min[y] = std::min(min[x], (i64)1LL * z);
        dep[y] = dep[x] + 1;
        dfs(y, x);
      }
    return void();
  }
  i32 lca(i32 x, i32 y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 20; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 20; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  void add(i32 x, i32 y) {
    g[x].eb(y);
    g[y].eb(x);
    return void();
  }
  void dfs2(i32 x, i32 f) {
    dp[x] = 0;
    for (i32 &y : g[x])
      if (y != f) {
        dfs2(y, x);
        dp[x] += dp[y];
      }
    if (vis[x]) {
      dp[x] = min[x];
    } else {
      dp[x] = std::min(dp[x], min[x]);	
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].eb(v, w), e[v].eb(u, w);
    }
    min[1] = 5e10 + 5;
    dfs(1, 1);
    q = read();
    while (q--) {
      m = read();
      p.clear(), vec.clear();
      for (i32 i = 1; i <= m; ++i) p.eb(read());
      std::sort(all(p), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
      st[top = 1] = 1;
      for (i32 &v : p) {
      	vis[v] = true;
      	vec.eb(v);
        if (v != 1) {
          i32 L = lca(st[top], v);
          if (L != st[top]) {
            while (dfn[st[top - 1]] > dfn[L]) {
              add(st[top - 1], st[top]);
              top--;
            }
            if (dfn[st[top - 1]] < dfn[L]) {
              vec.eb(L);
              add(L, st[top]);
              st[top] = L;
            } else {
              add(L, st[top]);
              top--;
            }
          }
          st[++top] = v;
        }
      }
      vec.eb(1);
	  for (i32 i = 1; i < top; ++i) add(st[i], st[i + 1]);
      dfs2(1, 1);
      fprintf(fout, "%lld\n", dp[1]);
      for (i32 &v : vec) g[v].clear();
      for (i32 &v : p) vis[v] = false;
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P2495::main(), 0; }

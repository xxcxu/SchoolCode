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
namespace Solution_Of_CF613D {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, q;
  i32 dfn[N], tim = 0;
  i32 st[N], top = 0;
  i32 dep[N], anc[N][22];
  i32 dp[N];
  bool vis[N], vis2[N];
  std::vector<i32> p, vec;
  std::vector<i32> e[N], g[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    dfn[x] = ++tim;
    anc[x][0] = fa;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &y : e[x])
      if (y != fa) {
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
  void add(i32 x, i32 y) {
    g[x].eb(y), g[y].eb(x);
    return void();
  }
  bool check(i32 x, i32 fa) {
    bool f = true;
    for (i32 y : g[x])
      if (y != fa) {
        f &= check(y, x);
        f &= !(vis[x] && vis[y] && (dep[y] - dep[x] == 1));
      }
    return f;
  }
  void dfs2(i32 x, i32 fa) {
    i32 cnt = 0;
    dp[x] = vis2[x] = 0;
    for (i32 y : g[x])
      if (y != fa) {
        dfs2(y, x);
        dp[x] += dp[y];
        if (vis2[y]) ++cnt;
      }
    if (vis[x]) {
      for (i32 y : g[x])
        if (y != fa)
          if (vis2[y]) ++dp[x];	
    vis2[x] = true;
    } else {
      if (cnt > 1) ++dp[x]; 
      else if (cnt == 1) vis2[x] = true;
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
      st[top = 1] = 1; vec.eb(1);
      for (auto &v : p) vis[v] = true, vec.eb(v);
      for (auto &v : p)
        if (v != 1) {
          i32 L = lca(st[top], v);
          if (L != st[top]) {
            while (dfn[L] < dfn[st[top - 1]]) {
              add(st[top - 1], st[top]);
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
      for (i32 i = 1; i < top; ++i) add(st[i], st[i + 1]);
      bool f = check(1, 1);
      if (f) {
        dfs2(1, 1);
        fprintf(fout, "%d\n", dp[1]);
      } else {
        fputs("-1\n", fout);
      }
      for (auto &v : p) vis[v] = false; 
      for (auto &v : vec) g[v].clear();
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF613D::main(), 0; }

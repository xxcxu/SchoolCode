#pragma GCC optimize(3)
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
namespace Solution_Of_HLP1660 {
  bool _1;
  static const i32 N = 400005, M = 1000005;
  i32 n, m, mdep, rt;
  i32 ans[N], dep[N];
  i32 u[N], v[N];
  bool vis[N], vis2[N];
  std::vector<i32> p, eg[M], e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    vis[x] = true;
    for (i32 y : e[x])
      if (y != fa) {
        dep[y] = dep[x] + 1;
        if (chkmax(mdep, dep[y])) rt = y;
        dfs(y, x);
      }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("walk.in", "r");
    fout = fopen("walk.out", "w");
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 w;
      u[i] = read(), v[i] = read(), w = read();
      eg[w].eb(i);
      chkmax(m, w);
    }
    for (i32 g = m; g >= 1; --g) {
      p.clear();
      for (i32 i = g; i <= m; i += g)
        for (i32 j : eg[i]) {
          e[u[j]].eb(v[j]), e[v[j]].eb(u[j]);
          if (!vis2[u[j]]) p.eb(u[j]);
          if (!vis2[v[j]]) p.eb(v[j]);
        }
      for (i32 q : p)
        if (!vis[q]) {
          mdep = 0;
          dep[q] = 0, dfs(q, 0);
          dep[rt] = 0, dfs(rt, 0);
          chkmax(ans[mdep], g);
        }
      for (i32 q : p) vis[q] = vis2[q] = false, e[q].clear();
    }
    for (i32 i = n; i >= 1; --i) chkmax(ans[i], ans[i + 1]);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1660::main(), 0; }

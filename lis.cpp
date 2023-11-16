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
namespace Solution_Of_lis {
  bool _1;
  static const i32 N = 4005;
  i32 n, res, ts;
  i32 w[N];
  std::vector<i32> e[N];
  i32 f[N], g[N], anc[N], son[N], dep[N];
  i32 dfn[N], redfn[N], size[N], top[N];
  bool _2;
  void dfs(i32 u, i32 fa) {
    size[u] = 1;
    anc[u] = fa;
    dep[u] = dep[fa] + 1;
    son[u] = 0;
    for (i32 v : e[u])
      if (v != fa) {
        dfs(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
          son[u] = v;
      }
    return void();
  }
  void dfs3(i32 u, i32 t) {
    top[u] = t;
    dfn[u] = ++ts;
    redfn[ts] = u;
    if (son[u]) dfs3(son[u], t);
    for (i32 v : e[u])
      if (v != anc[u] && v != son[u])
        dfs3(v, v);
    return void();
  }
  i32 lca(i32 u, i32 v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
      u = anc[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
  void dfs2(i32 u, i32 fa) {
    f[u] = g[u] = 1;
    for (i32 v : e[u])
      if (v != fa)
        dfs2(v, u);
    for (i32 i = dfn[u] + 1; i < dfn[u] + size[u]; ++i) {
      if (w[redfn[i]] < w[u]) chkmax(f[u], f[redfn[i]] + 1);
      if (w[redfn[i]] > w[u]) chkmax(g[u], g[redfn[i]] + 1);
    }
    for (i32 i = dfn[u]; i < dfn[u] + size[u]; ++i)
      for (i32 j = dfn[u]; j < dfn[u] + size[u]; ++j)
        if (lca(i, j) == u) {
          if (w[redfn[i]] < w[redfn[j]]) chkmax(res, f[redfn[i]] + g[redfn[j]]);
          if (w[redfn[i]] > w[redfn[j]]) chkmax(res, g[redfn[i]] + f[redfn[j]]);
        }
    chkmax(res, f[u] + g[u] - 1);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("lis.in", "r");
    fout = fopen("lis.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    for (i32 i = 1; i <= n; ++i) w[i] = read();
    i32 ans = n;
    if (n == 1) return fputs("0\n", fout), void();
    for (i32 i = 1; i <= n; ++i) {
      res = 1;
      dep[i] = 0;
      for (i32 j : e[i]) {
        ts = 0;
        dfs(j, i);
        dfs3(j, j);
        dfs2(j, i);
      }
      chkmin(ans, res);
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_lis::main(), 0; }
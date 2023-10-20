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
namespace Solution_Of_ARC098F {
  bool _1;
  static const i32 N = 100005;
  i32 n, m;
  i64 a[N], b[N], c[N], d[N], sb[N], dp[N], fa[N];
  bool vis[N];
  std::vector<i32> e[N], g[N];
  bool _2;
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void dfs1(i32 x) {
    sb[x] = b[x];
    for (i32 y : e[x]) {
      dfs1(y);
      sb[x] += sb[y];
    }
    return void();
  }
  void dfs2(i32 x) {
    if (!size(e[x])) dp[x] = c[x] + b[x];
    else dp[x] = LONG_LONG_MAX;
    for (i32 y : e[x]) {
      dfs2(y);
      dp[x] = std::min(dp[x], std::max(dp[y], c[x]) + sb[x] - sb[y]);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), b[i] = read();
    for (i32 i = 1; i <= n; ++i) c[i] = std::max(a[i] - b[i], (i64)0), d[i] = i;
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      g[u].eb(v), g[v].eb(u);
    }
    i64 Start_Time_Without_Read = clock();
    std::sort(d + 1, d + n + 1, [&](const i32 &x, const i32 &y) { return c[x] < c[y]; });
    for (i32 i = 1; i <= n; ++i) fa[i] = i;
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j : g[d[i]]) {
        if (vis[j]) {
          i32 fx = find(d[i]), fy = find(j); 
          if (fx != fy) {
            fa[fy] = fx;
            e[d[i]].eb(fy);
          }
        }
      }
      vis[d[i]] = true;
    }
    dfs1(d[n]);
    dfs2(d[n]);
    fprintf(fout, "%lld\n", dp[d[n]]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_ARC098F::main(), 0; }
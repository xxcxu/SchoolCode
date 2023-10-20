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
namespace Solution_Of_P3953 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, K, P;
  i32 dp[N][55], d[N];
  bool ins[N][55];
  bool vis[N];
  std::vector<std::pair<i32, i32>> e[N], g[N];
  bool inf;
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  std::priority_queue<std::pair<i32, i32>> q;
  void dijkstra() {
    std::memset(vis, 0, sizeof vis);
    std::memset(d, 0x3f, sizeof d);
    d[1] = 0;
    q.ep(0, 1);
    while (q.size()) {
      i32 x = q.top().second;
      q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto &[y, z] : e[x])
        if (d[y] > d[x] + z) {
          d[y] = d[x] + z;
          q.ep(-d[y], y);
        }
    }
    return void();
  }
  i32 dfs(i32 x, i32 l) {
    if (l < 0) return 0;
    if (ins[x][l]) return inf = true, 0;
    if (dp[x][l]) return dp[x][l];
    ins[x][l] = true;
    for (auto &[y, z] : g[x]) {
      dp[x][l] = inc(dp[x][l], dfs(y, l + d[x] - d[y] - z)); 
      if (inf) return 0;
    }
    ins[x][l] = false;
    return dp[x][l];
  }
  void solve() {
    inf = false;
    n = read(), m = read(), K = read(), P = read();
    for (i32 i = 1; i <= n; ++i) e[i].clear(), g[i].clear();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].eb(v, w), g[v].eb(u, w); 
    }
    std::memset(dp, 0, sizeof dp);
    std::memset(ins, 0, sizeof ins);
    dijkstra();
    dfs(1, 0);
    dp[1][0] = 1;
    i32 ans = 0;
    for (i32 i = 0; i <= K; ++i)
      ans = inc(ans, dfs(n, i));
    if (inf) fputs("-1\n", fout);
    else fprintf(fout, "%d\n", ans);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P3953::main(), 0; }
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
namespace Solution_Of_HLP1551 {
  bool _1;
  static const i32 N = 200005;
  i32 n, m, t;
  i64 len;
  i32 p[N];
  i64 dp[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x) {
    for (i32 y : e[x]) {
      dfs(y);
      chkmax(dp[x], dp[y] + 1);
    }
    return void();
  }
  void dfs2(i32 x) {
    dp[x] = 0;
    if (!(e[x].size()) && x != 1)
      dp[x] += 1LL * (m - 1) * t;
    for (i32 y : e[x]) {
      dfs2(y);
      len = std::max(len, dp[x] + dp[y] + 2);
      dp[x] = std::max(dp[x], dp[y] + 1);
    }
    len = std::max(len, dp[x] + 1);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tree.in", "r");
    fout = fopen("tree.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 2; i <= n; ++i) p[i] = read();
    for (i32 i = 2; i <= n; ++i) e[p[i]].eb(i);
    dfs(1);
    t = dp[1] + 1;
    dfs2(1);
    fprintf(fout, "%lld\n", len);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1551::main(), 0; }
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
  i32 n, m, len;
  i32 p[N], dp[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x) {
    for (i32 y : e[x]) {
      dfs(y);
      if (dp[x]) chkmax(len, dp[x] + dp[y] + 2);
      chkmax(dp[x], dp[y] + 1);
    }
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
    if (n == 1) fputs("1\n", fout);
    else {
      if (len >= dp[1] + 1) fprintf(fout, "%lld\n", len + 2ll * (dp[1] + 1) * (m - 1));
      else {
        i64 ans = std::max(len + 2ll * (dp[1] + 1) * (m - 1), 1ll * (dp[1] + 1) * m);
        fprintf(fout, "%lld\n", ans);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1551::main(), 0; }
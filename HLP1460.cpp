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
i64 read() {
  i64 t = 0, f = 0;
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
namespace Solution_Of_HLP1460 {
  bool _1;
  static const i32 N = 55;
  i32 n; i64 k;
  i64 dp[N][2];
  bool _2;
  i64 dfs(i32 n, i64 k) {
    if (n == 1) return 3LL;
    if (k > dp[n][1]) assert(0);
    if (k == dp[n][1]) return dp[n][0] + dp[n][1];
    else {
      i64 c1 = dp[n - 2][1];
      if (k <= c1) return dfs(n - 2, k);
      if (k <= 2 * c1) return dp[n - 2][0] + dp[n - 2][1] + dfs(n - 2, k - c1);
      return (dp[n - 2][0] + dp[n - 2][1]) * 2 + dfs(n - 1, k - 2 * c1);
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read();
    i64 Start_Time_Without_Read = clock(); 
    dp[0][1] = 1, dp[0][0] = 0;
    for (i32 i = 1; i <= n; ++i) {
      dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
      dp[i][0] = dp[i - 1][1] * 2;
    }
    fprintf(fout, "%lld\n", dfs(n, k));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1460::main(), 0; }
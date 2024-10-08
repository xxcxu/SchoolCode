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
namespace Solution_Of_CF1874D {
  bool _1;
  static const i32 N = 3005;
  i32 n, m;
  double dp[N][N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 0; i <= n; ++i)
      for (i32 j = 0; j <= m; ++j)
        dp[i][j] = 1e18;
    dp[0][0] = 0;
    for (i32 i = 0; i < n; ++i)
      for (i32 s = 0; s <= m; ++s)
        for (i32 j = 1; s + (n - i) * j <= m; ++j)
          chkmin(dp[i + 1][s + j], dp[i][s] + 1.0 * s / j);
    fprintf(fout, "%.9lf\n", 2 * dp[n][m] + n);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1874D::main(), 0; }
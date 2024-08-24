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
namespace Solution_Of_CF367E {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 1000000007;
  i32 n, m, p;
  i32 fac[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), p = read();
    if (n > m) return fputs("0\n", fout), void();
    std::vector<std::vector<std::vector<i32>>> dp(m + 1, std::vector<std::vector<i32>>(n + 1, std::vector<i32>(n + 1, 0)));
    dp[0][0][0] = 1;
    for (i32 i = 1; i <= m; ++i)
      for (i32 j = 0; j <= n; ++j)
        for (i32 k = 0; k <= j; ++k) {
          if (i != p) dp[i][j][k] = inc(dp[i][j][k], dp[i - 1][j][k]);
          if (j && j > k) dp[i][j][k] = inc(dp[i][j][k], dp[i - 1][j - 1][k]);
          if (k && i != p) dp[i][j][k] = inc(dp[i][j][k], dp[i - 1][j][k - 1]);
          if (j && k) dp[i][j][k] = inc(dp[i][j][k], dp[i - 1][j - 1][k - 1]);
        }
    fac[0] = 1;
    for (i32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    fprintf(fout, "%d\n", mul(dp[m][n][n], fac[n]));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF367E::main(), 0; }
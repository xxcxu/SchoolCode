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
namespace Solution_Of_HLP1409 {
  bool _1;
  static const i32 N = 4005;
  static const i32 P = 998244353;
  i32 n;
  i32 w[N];
  i32 dp[N][N][2], f[N], g[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 sum_w[N];
  i32 ask1(i32 l, i32 r) { return dec(sum_w[r], sum_w[l - 1]); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) w[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) sum_w[i] = inc(sum_w[i - 1], w[i]); 
    for (i32 i = 1; i <= n; ++i) {
      dp[3][i][0] = mul(inc(ask1(i, n), mul(i - 1, w[i])), i); // a <= b
      dp[3][i][1] = inc(ask1(i, n), mul(i - 1, w[i])); 
    }
    for (i32 i = 3; i < n; ++i) {
      for (i32 j = 1; j <= n; ++j) {
        dp[i + 1][j][1] = inc(dp[i + 1][j][1], mul(dp[i][j][0], w[j])); // a <= b > c
        f[j] = inc(f[j], inc(dp[i][j][0], mul(dp[i][j][1], j - 1))); // a <= b || a > b
        g[j - 1] = inc(g[j - 1], mul(dp[i][j][1], w[j])); // a > b
      }
      for (i32 j = 1; j <= n; ++j) f[j] = inc(f[j], f[j - 1]);
      for (i32 j = n; j >= 1; --j) g[j] = inc(g[j], g[j + 1]);
      for (i32 j = 1; j <= n; ++j) {
        dp[i + 1][j][0] = inc(dp[i + 1][j][0], mul(f[j], w[j])); // max(a, b) <= j && b <= c
        dp[i + 1][j][0] = inc(dp[i + 1][j][0], mul(g[j], j));
        dp[i + 1][j][1] = inc(dp[i + 1][j][1], g[j]);
      }
      for (i32 j = 1; j <= n; ++j) f[j] = g[j] = 0;
    }
    i32 ans = 0;
    for (i32 i = 1; i <= n; ++i)
      ans = inc(ans, inc(dp[n][i][0], mul(dp[n][i][1], i - 1)));
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1409::main(), 0; }
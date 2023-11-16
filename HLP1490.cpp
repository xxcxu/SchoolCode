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
namespace Solution_Of_HLP1490 {
  bool _1;
  static const i32 N = 2005;
  static const i32 P = 998244353;
  i32 n, m;
  char s[N][N];
  i32 f[N][N], g[N][N], h[N][N], dp[N][N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 inv(i32 x) { return qpow(x, P - 2); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("grid.in", "r");
    fout = fopen("grid.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) fscanf(fin, "%s", s[i] + 1);
    f[1][1] = s[1][1] - '0', g[1][1] = s[1][1] - '0', h[1][1] = 1, dp[1][1] = 1;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1 + (i == 1); j <= m; ++j) {
        h[i][j] = inc(h[i - 1][j], h[i][j - 1]);
        if (s[i][j] == '+') {
          f[i][j] = inc(f[i - 1][j], f[i][j - 1]);
          g[i][j] = 0;
          dp[i][j] = h[i][j];
        }
        else if (s[i][j] == '*') {
          f[i][j] = inc(dec(f[i - 1][j], g[i - 1][j]), dec(f[i][j - 1], g[i][j - 1]));
          g[i][j] = inc(g[i - 1][j], g[i][j - 1]);
          dp[i][j] = inc(g[i - 1][j], g[i][j - 1]);
        }
        else {
          auto update = [&](i32 x, i32 y)->void {
            if (s[x][y] == '+') {
              f[i][j] = inc(f[i][j], f[x][y], mul(h[x][y], s[i][j] - '0'));
              g[i][j] = inc(g[i][j], mul(h[x][y], s[i][j] - '0'));
              dp[i][j] = inc(dp[i][j], dp[x][y]);
            }
            if (s[x][y] == '*') {
              f[i][j] = inc(f[i][j], f[x][y], mul(g[x][y], s[i][j] - '0'));
              g[i][j] = inc(g[i][j], mul(g[x][y], s[i][j] - '0'));
              dp[i][j] = inc(dp[i][j], dp[x][y]);
            }
            if (isdigit(s[x][y])) {
              f[i][j] = inc(f[i][j], dec(f[x][y], g[x][y]), inc(mul(dp[x][y], s[i][j] - '0'), mul(g[x][y], 10)));
              g[i][j] = inc(g[i][j], inc(mul(dp[x][y], s[i][j] - '0'), mul(g[x][y], 10)));
              dp[i][j] = inc(dp[i][j], dp[x][y]);
            }
          };
          update(i - 1, j);
          update(i, j - 1);
        }
      }
    fprintf(fout, "%d\n", f[n][m]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1490::main(), 0; }
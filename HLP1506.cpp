/*
弹丸论破狂喜 弹丸论破狂喜
弹丸论破狂喜 弹丸论破狂喜
弹丸论破狂喜 弹丸论破狂喜
*/
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
namespace Solution_Of_HLP1506 {
  bool _1;
  static const i32 N = 205;
  static const i64 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 n, l, ans;
  i32 p[N], q[N], t[N];
  i64 dp[N][N][N][2];
  bool _2;
  i32 calc(i32 p, i32 o, i32 p2, i32 o2) {
    if (o == o2) return std::abs(p - p2);
    else return l - std::abs(p - p2);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), l = read();
    for (i32 i = 1; i <= n; ++i) p[i] = read();
    for (i32 i = 1; i <= n; ++i) q[i] = l - p[i];
    for (i32 i = 1; i <= n; ++i) t[i] = read();
    std::memset(dp, 0x3f, sizeof dp);
    t[n + 1] = t[0] = 0;
    p[n + 1] = l; p[0] = 0;
    q[n + 1] = 0; q[0] = l;
    dp[0][n + 1][0][0] = dp[0][n + 1][0][1] = 0;
    for (i32 i = 0; i <= n; ++i)
      for (i32 j = n + 1; j > i + 1; --j)
        for (i32 k = 0; k <= i + n + 1 - j; ++k)
          for (i32 op = 0; op < 2; ++op) {
            if (t[i + 1] >= dp[i][j][k][op] + calc(op ? p[j] : p[i], op, p[i + 1], 0)) {
              chkmin(dp[i + 1][j][k + 1][0], dp[i][j][k][op] + calc(op ? p[j] : p[i], op, p[i + 1], 0));
            } else {
              chkmin(dp[i + 1][j][k][0], dp[i][j][k][op] + calc(op ? p[j] : p[i], op, p[i + 1], 0));
            }
            if (t[j - 1] >= dp[i][j][k][op] + calc(op ? p[j] : p[i], op, p[j - 1], 1)) {
              chkmin(dp[i][j - 1][k + 1][1], dp[i][j][k][op] + calc(op ? p[j] : p[i], op, p[j - 1], 1));
            } else {
              chkmin(dp[i][j - 1][k][1], dp[i][j][k][op] + calc(op ? p[j] : p[i], op, p[j - 1], 1));
            }
          }
    for (i32 i = 0; i <= n; ++i)
      for (i32 j = n; j >= 0; --j)
        if (dp[i][i + 1][j][0] != inf64 || dp[i][i + 1][j][1] != inf64)
          { ans = std::max(ans, j); break; }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1506::main(), 0; }
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
namespace Solution_Of_HLP1466 {
  bool _1;
  static const i32 N = 5005;
  i32 n;
  i32 a[N], b[N];
  i64 dp[N][N], pre[N][N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("cards.in", "r");
    fout = fopen("cards.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i)
      a[i] = read(), b[i] = read();
    i64 Start_Time_Without_Read = clock();
    dp[n + 1][0] = 0;
    for (i32 i = n; i >= 1; --i) {
      for (i32 j = 0; j <= (n - i + 1); ++j) {
        if (j < n - i + 1)
          if (chkmax(dp[i][j], dp[i + 1][j] + 1ll * j * a[i]))
            pre[i][j] = j; // 打出力量加成
        if (j > 0)
          if (chkmax(dp[i][j], dp[i + 1][j - 1] + b[i]))
            pre[i][j] = j - 1; // 打出杀
      }
    }
    i64 ans = 0, pos = 0;
    for (i32 j = 0; j <= n; ++j)
      if (chkmax(ans, dp[1][j])) pos = j;
    fprintf(fout, "%lld\n", ans);
    for (i32 i = 2; i <= n; ++i) {
      fprintf(fout, "%d ", pos == pre[i - 1][pos] ? 1 : 2);
      pos = pre[i - 1][pos];
    }
    fprintf(fout, "%d\n", pos ? 2 : 1);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1466::main(), 0; }
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
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
namespace Solution_Of_block {
  bool _1;
  static const i32 N = 2005;
  i32 n, m, ans;
  char s[N], t[N];
  i32 dp[N][N][2];
  bool _2;
  char opt(i32 o) { return o ? 'I' : 'O'; }
  bool check(i32 x, i32 y, i32 o, i32 oo) {
    i32 v = dp[x][y][o];
    if (v == 0 && oo == 0) return false;
    return true;
  }
  void trans(i32 x, i32 y, i32 o) {
    if (x && s[x] == opt(o) && check(x - 1, y, o ^ 1, o)) chkmax(dp[x][y][o], dp[x - 1][y][o ^ 1] + 1);
    if (y && t[y] == opt(o) && check(x, y - 1, o ^ 1, o)) chkmax(dp[x][y][o], dp[x][y - 1][o ^ 1] + 1); 
    if (t[y] == opt(o) && check(x, 0, o ^ 1, o)) chkmax(dp[x][y][o], dp[x][0][o ^ 1] + 1);
    if (s[x] == opt(o) && check(x, 0, o ^ 1, o)) chkmax(dp[x][y][o], dp[0][y][o ^ 1] + 1);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("block.in", "r");
    fout = fopen("block.out", "w");
    n = read(), m = read();
    fscanf(fin, "%s %s", s + 1, t + 1);
    for (i32 i = 0; i <= n; ++i)
      for (i32 j = 0; j <= m; ++j) {
        trans(i, j, 0);
        trans(i, j, 1);
        ans = std::max(ans, dp[i][j][1]);
      }
    fprintf(fout, "%d\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_block::main(), 0; }
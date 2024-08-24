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
namespace Solution_Of_H1035 {
  bool _1;
  static const i32 N = 75;
  i32 n, m;
  std::bitset<15005> dp[N][N][N];
  char s[N];
  bool _2;
  void dfs(i32 x, i32 w, i32 y, i32 k) {
    if (x == 0) return void();
    if (w && (s[x] == 'w' || s[x] == '?')) if (dp[x - 1][w - 1][y][k]) return dfs(x - 1, w - 1, y, k), fputc('w', fout), void();
    if (s[x] == 'y' || s[x] == '?') if (dp[x - 1][w][y + 1][k]) return dfs(x - 1, w, y + 1, k), fputc('y', fout), void();
    if (s[x] == 'm' || s[x] == '?') if (k >= w * y && dp[x - 1][w][y][k - w * y]) return dfs(x - 1, w, y, k - w * y), fputc('m', fout), void();
    if (s[x] != 'w' && s[x] != 'm' && s[x] != 'y') if (dp[x - 1][w][y][k]) return dfs(x - 1, w, y, k), fputc(s[x] == '?' ? 'p' : s[x], fout), void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    fscanf(fin, "%s", s + 1);
    for (i32 i = 0; i <= n; ++i) dp[0][0][i] = true;
    for (i32 i = 1; i <= n; ++i) {
      for (i32 w = 0; w <= n; ++w)
        for (i32 y = 0; y <= n - i; ++y) {
          if (w && (s[i] == 'w' || s[i] == '?')) dp[i][w][y] |= dp[i - 1][w - 1][y];
          if (s[i] == 'y' || s[i] == '?') dp[i][w][y] |= dp[i - 1][w][y + 1]; 
          if (s[i] == 'm' || s[i] == '?') dp[i][w][y] |= (dp[i - 1][w][y] << (w * y));
          if (s[i] != 'w' && s[i] != 'm' && s[i] != 'y') dp[i][w][y] |= dp[i - 1][w][y];
        }
    }
    for (i32 w = 0; w <= n; ++w)
      if (dp[n][w][0][m]) {
        dfs(n, w, 0, m);
        return void();
      }
    fputs("-1\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_H1035::main(), 0; }
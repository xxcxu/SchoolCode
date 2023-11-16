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
namespace Solution_Of_HLP1552 {
  bool _1;
  static const i32 N = 505;
  i32 n, m, k;
  std::vector<std::pair<i32, i32>> c[2];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("gomoku.in", "r");
    fout = fopen("gomoku.out", "w");  
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), k = read();
    if (k == 1) {
      fputs("-1\n", fout);
    }
    if (k == 2) {
      if (n == 1 && m == 1) {
        fputs("1 1\n", fout);
      }
      if (n == 1 && m == 2) {
        fputs("1 1\n", fout);
        fputs("1 2\n", fout);
      }
      if (n == 2 && m == 1) {
        fputs("1 1\n", fout);
        fputs("2 1\n", fout);
      }
      if (n >= 2 && m >= 2) {
        fputs("-1\n", fout);
      }
    }
    if (k >= 3) {
      for (i32 i = 1; i <= n; ++i) {
        for (i32 j = 1; j <= m; j += 4) {
          if (i & 1) {
            c[0].eb(i, j);
            if (j + 1 <= m) c[1].eb(i, j + 1);
            if (j + 2 <= m) c[1].eb(i, j + 2);
            if (j + 3 <= m) c[0].eb(i, j + 3);
          } else {
            c[1].eb(i, j);
            if (j + 1 <= m) c[0].eb(i, j + 1);
            if (j + 2 <= m) c[0].eb(i, j + 2);
            if (j + 3 <= m) c[1].eb(i, j + 3);
          }
        }
      }
      if (c[0].size() < c[1].size()) std::swap(c[0], c[1]);
      for (i32 i = 0; i < c[1].size(); ++i) {
        fprintf(fout, "%d %d\n", c[0][i].first, c[0][i].second);
        fprintf(fout, "%d %d\n", c[1][i].first, c[1][i].second);
      }
      if (c[0].size() > c[1].size()) fprintf(fout, "%d %d\n", c[0].back().first, c[0].back().second);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1552::main(), 0; }
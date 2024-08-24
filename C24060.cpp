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
namespace Solution_Of_C24060 {
  bool _1;
  static const i32 N = 305;
  i32 n, k;
  char s[N], t[N];
  i32 f[N][N][N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), k = read();
    fscanf(fin, "%s%s", s + 1, t + 1);
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j = 1; j <= n; ++j) {
        for (i32 p = 0; p <= k; ++p) {
          chkmax(f[i][j][p], f[i - 1][j][p]);
          chkmax(f[i][j][p], f[i][j - 1][p]);
          if (p >= 1) chkmax(f[i][j][p], f[i][j][p - 1]);
          if (s[i] == t[j]) chkmax(f[i][j][p], f[i - 1][j - 1][p] + 1);
          else if (p >= 1) chkmax(f[i][j][p], f[i - 1][j - 1][p - 1] + 1);
        }
      }
    }
    fprintf(fout, "%d\n", f[n][n][k]);
    // f[i][j][k] = i, j 两位用k次机会。    
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_C24060::main(), 0; }
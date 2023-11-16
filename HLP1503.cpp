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
namespace Solution_Of_HLP1503 {
  bool _1;
  static const i32 N = 100005;
  static const i32 dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}, dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
  static const i32 to0[5][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 2, 3, 2, 5, 2, 2, 3, 5}, {0, 1, 4, 1, 1, 4, 6, 3, 4}, {0, 0, 1, 2, 5, 5, 0, 0, 5}, {0, -1, 7, 6, 6, 1, 6, 6, 6}};
  static const i32 to1[5][6] = {{0, 0, 0, 0, 0, 0}, {0, 3, 2, 5, 3, 5}, {0, 3, 1, 3, 3, 5}, {0, 0, 0, 5, 0, 5}, {0, 0, 1, 6, 0, -1}};
  static const i32 to2[5][7] = {{0, 0, 0, 0, 0, 0, 0}, {0, 2, 4, 2, 3, 3, 5}, {0, 2, 4, 1, 6, 3, 6}, {0, 2, 0, 2, 5, 0, 5}, {0, -1, 7, 7, 6, 0, 6}};
  static const i32 to3[5][4] = {{0, 0, 0, 0}, {0, 3, 3, 5}, {0, 3, 3, 5}, {0, 0, 0, 5}, {0, 0, 0, -1}};
  static const i32 link[5][5] = {{0, 0, 0, 0, 0}, {0, 2, 4, 3, 5}, {0, 4, 3, 3, 6}, {0, 7, 0, 0, 5}, {0, 1, 7, 0, 6}};
  i32 n;
  i32 nxt[5][N];
  bool _2;
  void solve() {
    n = read();
    if (n <= 2 || n == 4) return fputs("No\n", fout), void();
    else fputs("Yes\n", fout);
    i32 m = -1;
    if (n % 4 == 0) {
      m = 8;
      for (i32 i = 1; i <= 4; ++i)
        for (i32 j = 1; j <= m; ++j)
          nxt[i][j] = to0[i][j];
    }
    if (n % 4 == 1) {
      m = 5;
      for (i32 i = 1; i <= 4; ++i)
        for (i32 j = 1; j <= m; ++j)
          nxt[i][j] = to1[i][j];
    }
    if (n % 4 == 2) {
      m = 6;
      for (i32 i = 1; i <= 4; ++i)
        for (i32 j = 1; j <= m; ++j)
          nxt[i][j] = to2[i][j];
    }
    if (n % 4 == 3) {
      m = 3;
      for (i32 i = 1; i <= 4; ++i)
        for (i32 j = 1; j <= m; ++j)
          nxt[i][j] = to3[i][j];
    }
    while (m < n) {
      nxt[2][m - 1] = 1, nxt[3][m - 1] = 2;
      for (i32 i = 1; i <= 4; ++i)
        for (i32 j = 1; j <= 4; ++j)
          nxt[i][m + j] = link[i][j];
      m += 4;
    }
    i32 sx = 1, sy = 1;
    for (i32 i = 1; i <= 4 * n; ++i) {
      fprintf(fout, "%d %d\n", sx, sy);
      if (i < 4 * n) {
        i32 tx = dx[nxt[sx][sy]], ty = dy[nxt[sx][sy]];
        sx += tx, sy += ty;
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("horse.in", "r");
    fout = fopen("horse.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1503::main(), 0; }
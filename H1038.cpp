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
namespace Solution_Of_H1038 {
  bool _1;
  i32 t, n;
  bool _2;
  void solve1() {
    n = read();
    i32 x, y;
    x = read(), y = read();
    if (x % 4 == 1 && y % 2 == 0) {
      fputs("Yes\n", fout);
      for (i32 i = 1; i < x; i += 4) fprintf(fout, "%d %d %d %d\n", i, i + 1, i + 2, i + 3);
      for (i32 i = x + 1; i < y; i += 4) fprintf(fout, "%d %d %d %d\n", i, i + 1, i + 2, i + 3);
      for (i32 i = y + 1; i <= n * 4 + 2; i += 4) fprintf(fout, "%d %d %d %d\n", i, i + 1, i + 2, i + 3);
    } else if (x % 4 == 2 && y % 1 == 0) {
      if (y - x != 3) {
        for (i32 i = 1; i < x - 1; i += 4) fprintf(fout, "%d %d %d %d\n", i, i + 1, i + 2, i + 3);
        for (i32 i = y + 2; i <= n * 4 + 2; i += 4) fprintf(fout, "%d %d %d %d\n", i, i + 1, i + 2, i + 3);
        n = (y - x + 1) / 4;
        for (i32 i = 1; i <= n; ++i)
          if (i != 2) fprintf(fout, "%d %d %d %d\n", x + i, x + i + n, x + i + n * 2, x + i + n * 3);
          else fprintf(fout, "%d %d %d %d\n", x + 2 + n, x + 2 + 2 * n, x + 2 + 3 * n, x + 2 + 4 * n);
      } else {
        i32 A = std::min(x - 1, 4 * n + 2 - y);
        i32 B = std::max(x - 1, 4 * n + 2 - y);
        bool flag = ((x - 1) == A);
        auto print = [&](i32 x, i32 a, i32 b, i32 c, i32 d) {
          if (!x) {
            a = 4 * n + 2 - a + 1;
            b = 4 * n + 2 - b + 1;
            c = 4 * n + 2 - c + 1;
            d = 4 * n + 2 - d + 1;
          }
          fprintf(fout, "%d %d %d %d\n", a, b, c, d);
          return void();
        };
        if (n <= 5) fputs("No\n", fout);
        if (A >= 9) {
          if (B < 13) fputs("No\n", fout);
          else {
            for (i32 i = 1; i < x - 9; i += 4) print(flag, i, i + 1, i + 2, i + 3);
            for (i32 i = y + 22; i <= n * 4 + 2; i += 4) print(flag, i, i + 1, i + 2, i + 3);

          }
        } else if (A >= 5) {
          if (B < 21) fputs("No\n", fout);
          else {
            for (i32 i = 1; i < x - 5; i += 4) print(flag, i, i + 1, i + 2, i + 3);
            for (i32 i = y + 22; i <= n * 4 + 2; i += 4) print(flag, i, i + 1, i + 2, i + 3);

          }
        } else if (A >= 1) {
          if (B < 29) fputs("No\n", fout);
          else {
            for (i32 i = 1; i < x - 1; i += 4) print(flag, i, i + 1, i + 2, i + 3);
            for (i32 i = y + 30; i <= n * 4 + 2; i += 4) print(flag, i, i + 1, i + 2, i + 3);
            
          }
        }
      }
    }
    else fputs("No\n", fout)
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    t = read();
    if (t == 1) solve1();
    if (t == 2) solve2();
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_H1038::main(), 0; }
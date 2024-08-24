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
  i32 n, x, y, A;
  bool _2;
  i32 calc(i32 i) { return std::min(y, (i32)(1ll * A * i / x)); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), x = read(), y = read();
    A = (1ll * x * y + n - 1) / n;
    fprintf(fout, "%d\n", A);
    for (i32 i = 1; i <= x; ++i) fprintf(fout, "%d", 1);
    for (i32 i = 1; i <= n - x; ++i) fprintf(fout, "%d", 0);
    fputs("\n", fout);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d", calc(i) - calc(i - 1));
    fputs("\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_H1035::main(), 0; }
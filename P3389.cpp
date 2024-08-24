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
namespace Solution_Of_test {
  bool _1;
  static const i32 N = 105;
  static const double eps = 1e-8;
  i32 n;
  double a[N][N], b[N][N], ans[N];
  bool _2;
  bool iszero(double f) { return std::fabs(f) <= eps; }
  bool guass() {
    for (i32 i = 1; i <= n; ++i) {
      i32 p = -1;
      for (i32 j = i; j <= n; ++j) if (!iszero(a[j][i])) { p = j; break; }
      if (!~p) return false;
      if (p != i) for (i32 j = i; j <= n + 1; ++j) std::swap(a[i][j], a[p][j]);
      for (i32 j = i + 1; j <= n; ++j) {
        double rear = a[j][i] / a[i][i];
        for (i32 k = i; k <= n + 1; ++k) a[j][k] -= a[i][k] * rear;
      }
    }
    for (i32 i = n; i >= 1; --i) {
      ans[i] = a[i][n + 1] / a[i][i];
      for (i32 j = i - 1; j >= 1; --j) {
        double rear = a[j][i] / a[i][i];
        for (i32 k = 1; k <= n + 1; ++k) a[j][k] -= a[i][k] * rear;
      }
    }
    return true;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n + 1; ++j) fscanf(fin, "%lf", a[i] + j);
    if (guass())
      for (i32 i = 1; i <= n; ++i) fprintf(fout, "%.2lf\n", ans[i]);
    else
      fputs("No Solution", fout);
    fputs("\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_test::main(), 0; }
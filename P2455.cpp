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
  std::valarray<double> a[N];
  double ans[N];
  bool _2;
  bool iszero(double f) { return std::fabs(f) <= eps; }
  i32 guass() {
    i32 r = 1;
    for (i32 i = 1; i <= n; ++i) {
      i32 p = -1;
      for (i32 j = r; j <= n; ++j) if (!iszero(a[j][i])) { p = j; break; }
      if (!~p) continue;
      if (r != p) a[r].swap(a[p]);
      for (i32 j = r + 1; j <= n; ++j) {
        double rear = a[j][i] / a[r][i];
        a[j] -= rear * a[r];
      }
      ++r;
    }
    if (r <= n) {
      for (i32 i = r; i <= n; ++i)
        if (!iszero(a[i][n + 1])) return -1;
      return 0;
    }
    for (i32 i = n; i >= 1; --i) {
      ans[i] = a[i][n + 1] / a[i][i];
      for (i32 j = i - 1; j >= 1; --j) {
        double rear = a[j][i] / a[i][i];
        a[j] -= rear * a[i];
      }
    }
    return 1;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i].resize(n + 2);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n + 1; ++j) fscanf(fin, "%lf", &a[i][j]);
    i32 foo = guass();
    if (foo == 1) for (i32 i = 1; i <= n; ++i) fprintf(fout, "x%d=%.2lf\n", i, ans[i]);
    else fprintf(fout, "%d\n", foo);
    fputs("\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_test::main(), 0; }
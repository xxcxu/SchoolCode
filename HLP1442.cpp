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
namespace Solution_Of_HLP1442 {
  bool _1;
  static const i32 N = 502;
  i32 n;
  std::vector<std::vector<double>> f[N << 2];
  struct Point {
    i32 x, y;
    Point() = default;
    Point(i32 _x, i32 _y): x(_x), y(_y) {}
  } a[N];
  bool _2;
  double sqr(double x) { return 1.0 * x * x; }
  double dis(i32 x, i32 y) {
    return std::sqrt(sqr(a[x].x - a[y].x) + sqr(a[x].y - a[y].y));
  }
  void pre_solve1(i32 l, i32 r);
  void pre_solve2(i32 l, i32 r);
  void pre_solve1(i32 l, i32 r) {
    if (l == r) return void();
    std::sort(a + l, a + r + 1, [&](const Point &a, const Point &b) { return a.x < b.x; });
    i32 nn = (r - l + 1) / 2;
    i32 mid = l + nn - 1;
    pre_solve2(l, mid);
    pre_solve2(mid + 1, r);
    return void();
  }
  void pre_solve2(i32 l, i32 r) {
    if (l == r) return void();
    std::sort(a + l, a + r + 1, [&](const Point &a, const Point &b) { return a.y < b.y; });
    i32 nn = (r - l + 1) / 2;
    i32 mid = l + nn - 1;
    pre_solve1(l, mid);
    pre_solve1(mid + 1, r);
    return void();
  }
  #define ls (x << 1)
  #define rs (x << 1 | 1)
  void solve(i32 x, i32 l, i32 r) {
    if (l == r) {
      f[x] = std::vector<std::vector<double>>(1, std::vector<double>(1, 0));
      return void();
    }
    i32 nn = (r - l + 1) / 2;
    i32 mid = l + nn - 1;
    solve(ls, l, mid);
    solve(rs, mid + 1, r);
    std::vector<std::vector<double>> g;
    f[x] = std::vector<std::vector<double>>(r - l + 1, std::vector<double>(r - l + 1, 1e18));
       g = std::vector<std::vector<double>>(r - l + 1, std::vector<double>(r - l + 1, 1e18));
    i32 len1 = mid - l + 1;
    i32 len2 = r - mid;
    for (i32 i = 0; i < len1; ++i)
      for (i32 j = 0; j < len1; ++j)
        if (i != j || (l == mid))
          for (i32 k = 0; k < len2; ++k)
            chkmin(g[i][k + nn], f[ls][i][j] + dis(j + l, k + mid + 1));
    for (i32 k = 0; k < len2; ++k)
      for (i32 o = 0; o < len2; ++o)
        if (k != o || (mid + 1 == r))
          for (i32 i = 0; i < len1; ++i)
            chkmin(g[k + nn][i], f[rs][k][o] + dis(o + mid + 1, i + l));
    for (i32 i = 0; i < len1; ++i)
      for (i32 k = 0; k < len2; ++k)
        for (i32 o = 0; o < len2; ++o)
          if (k != o || (mid + 1 == r))
            chkmin(f[x][i][o + nn], g[i][k + nn] + f[rs][k][o]);
    for (i32 k = 0; k < len2; ++k)
      for (i32 i = 0; i < len1; ++i)
        for (i32 j = 0; j < len1; ++j)
          if (i != j || (l == mid))
            chkmin(f[x][k + nn][j], g[k + nn][i] + f[ls][i][j]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("splitham.in", "r");
    fout = fopen("splitham.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i].x = read(), a[i].y = read();
    i64 Start_Time_Without_Read = clock();
    pre_solve1(1, n);
    solve(1, 1, n);
    double ans = 1e18;
    for (i32 i = 0; i < n; ++i)
      for (i32 j = 0; j < n; ++j)
        if (i != j || (n == 1))
          ans = std::min(ans, f[1][i][j]);
    fprintf(fout, "%.2lf\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1442::main(), 0; }
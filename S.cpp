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
namespace Solution_Of_S {
  bool _1;
  static const i32 N = 51;
  i32 n, m, q;
  i32 a[N], l[N], r[N];
  i32 cnt[N];
  i32 f[N][N][N][N];
  std::set<std::pair<i32, i32>> s[N][N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read(), q = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= q; ++i) l[i] = read(), r[i] = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= q; ++j)
        if (l[j] <= a[i] && a[i] <= r[j])
          ++cnt[i];
    for (i32 l = 1; l <= n; ++l)
      for (i32 r = l; r <= n; ++r)
        for (i32 i = l; i <= r; ++i)
          s[l][r].ep(a[i], i);
    a[n + 1] = (1e9 + 1);
    std::memset(f, 0x3f, sizeof f);
    for (i32 i = 1; i <= n; ++i) f[i][0][i][i] = 0;
    for (i32 i = 1; i <= n + 1; ++i)
      for (i32 j = 0; j <= m; ++j)
        for (i32 l = 1; l <= n; ++l)
          for (i32 r = l; r <= n; ++r) {
            auto it = s[l][r].lower_bound({a[i], i});
            if (it == s[l][r].begin()) continue;
            auto k = (*it).second;
            if (j) f[i][j][l][r] = std::min(f[i][j][l][r], f[k][j - 1][l][r]);
            for (i32 t = 0; t <= j; ++t) f[i][j][l][r] = std::min(f[i][j][l][r], cnt[k] * a[k] + f[k][t][l][k - 1] + f[k][j - t][k + 1][r]);
          }
    fprintf(fout, "%d\n", f[n + 1][m][1][n]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_S::main(), 0; }
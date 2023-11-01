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
namespace Solution_Of_HLP1462 {
  bool _1;
  static const i32 N = 505;
  static const i32 dx[] = {0, 0, 1, -1};
  static const i32 dy[] = {1, -1, 0, 0};
  static const i32 P = 998244353;
  i32 n, m, tot;
  i32 a[N][N], cnt[N][N];
  std::pair<i32, i32> b[N * N];
  i32 s[N][N], t[N][N];
  std::vector<std::pair<i32, i32>> e[N][N], g[N][N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; } 
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("grid.in", "r");
    fout = fopen("grid.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        a[i][j] = read(), b[++tot] = std::make_pair(i, j);
    i64 Start_Time_Without_Read = clock();
    std::sort(b + 1, b + tot + 1, [&](const std::pair<i32, i32> &x, const std::pair<i32, i32> &y) { return a[x.first][x.second] < a[y.first][y.second]; });
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        for (i32 d = 0; d < 4; ++d) {
          i32 nx = i + dx[d], ny = j + dy[d];
          if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
          ++cnt[i][j];
          if (a[i][j] > a[nx][ny]) e[i][j].eb(nx, ny);
          if (a[i][j] < a[nx][ny]) g[i][j].eb(nx, ny);
        }
    for (i32 i = 1; i <= tot; ++i) {
      auto &[x, y] = b[i];
      t[x][y] = 1;
      for (auto &[nx, ny] : e[x][y])
        t[x][y] = inc(t[x][y], t[nx][ny]);
    }
    for (i32 i = tot; i >= 1; --i) {
      auto &[x, y] = b[i];
      s[x][y] = cnt[x][y];
      for (auto &[nx, ny] : g[x][y])
        s[x][y] = inc(s[x][y], s[nx][ny]);
    }
    i32 ans = mul(n, n);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        ans = inc(ans, mul(t[i][j], cnt[i][j]));
    m = read();
    while (m--) {
      static i32 x, y;
      x = read(), y = read();
      fprintf(fout, "%d\n", dec(ans, mul(s[x][y], t[x][y])));
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1462::main(), 0; }
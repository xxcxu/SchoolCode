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
namespace Solution_Of_HLP1616 {
  bool _1;
  static const i32 N = 250005, M = 2505;
  i32 n;
  i32 r[N], c[N], maxx[M], maxy[M], minx[M], miny[M];
  i32 sum[M][M];
  bool vis1[M][M], vis2[M][M];
  i32 d1[M][M], d2[M][M];
  bool _2;
  i32 dfs1(i32 x, i32 y) {
    if (vis1[x][y]) return d1[x][y];
    vis1[x][y] = true;
    i32 t = sum[x][2500] - sum[x][y - 1];
    if (t == 0) return d1[x][y] = 0;
    return d1[x][y] = (t + dfs1(std::min(x, minx[y - 1]), std::max(y, maxy[x + 1])));
  }
  i32 dfs2(i32 x, i32 y) {
    if (vis2[x][y]) return d2[x][y];
    vis2[x][y] = true;
    i32 t = sum[2500][y] - sum[x - 1][y];
    if (t == 0) return d2[x][y] = 0;
    return d2[x][y] = (t + dfs2(std::max(x, maxx[y + 1]), std::min(y, miny[x - 1])));
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fin = fopen("assembly.in", "r");
    fout = fopen("assembly.out", "w");
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) r[i] = read(), c[i] = read();
    for (i32 i = 1; i <= n; ++i) ++sum[r[i]][c[i]];
    for (i32 i = 1; i <= 2500; ++i)
      for (i32 j = 1; j <= 2500; ++j)
        sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    std::memset(minx, 0x3f, sizeof minx);
    std::memset(miny, 0x3f, sizeof miny);
    for (i32 i = 1; i <= n; ++i) chkmin(minx[c[i]], r[i]), chkmax(maxx[c[i]], r[i]);
    for (i32 i = 1; i <= n; ++i) chkmin(miny[r[i]], c[i]), chkmax(maxy[r[i]], c[i]);
    for (i32 i = 1; i <= 2500; ++i) chkmin(minx[i], minx[i - 1]), chkmin(miny[i], miny[i - 1]);
    for (i32 i = 2500; i >= 1; --i) chkmax(maxx[i], maxx[i + 1]), chkmax(maxy[i], maxy[i + 1]);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", (n - 1) + (dfs1(r[i], c[i]) - 1) + (dfs2(r[i], c[i]) - 1));
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1616::main(), 0; }
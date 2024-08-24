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
namespace Solution_Of_CF113D {
  bool _1;
  static const i32 N = 23;
  static const double eps = 1e-8;
  i32 n, m, a, b, cnt;
  i32 id[N][N], deg[N];
  double p[N], ans[N * N];
  std::valarray<double> f[N * N];
  std::vector<i32> e[N];
  bool _2;
  void guass() {
    for (i32 i = 1; i <= cnt; ++i) {
      i32 pos = -1;
      for (i32 j = i; j <= cnt; ++j)
        if (std::fabs(f[j][i]) >= eps)
          { pos = j; break; }
      assert(~pos);
      if (i != pos) f[i].swap(f[pos]);
      assert(std::fabs(f[i][i]) >= eps);
      for (i32 j = i + 1; j <= cnt; ++j) {
        double rear = f[j][i] / f[i][i];
        f[j] -= rear * f[i];
      }
    }
    for (i32 i = cnt; i >= 1; --i) {
      assert(std::fabs(f[i][i]) >= eps);
      ans[i] = f[i][cnt + 1] / f[i][i];
      for (i32 j = i - 1; j >= 1; --j) {
        double rear = f[j][i] / f[i][i];
        f[j] -= rear * f[i]; 
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read(), a = read(), b = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
      ++deg[u], ++deg[v];
    }
    for (i32 i = 1; i <= n; ++i) fscanf(fin, "%lf", p + i);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j) id[i][j] = ++cnt;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j) f[id[i][j]].resize(cnt + 2);
    f[id[a][b]][cnt + 1] = -1;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j) {
        if (i == j) {
          f[id[i][j]][id[i][j]] = -1.0;
          for (i32 &k : e[i]) if (k != j) f[id[i][j]][id[k][j]] = (1.0 - p[k]) * p[j] / deg[k];
          for (i32 &k : e[j]) if (k != i) f[id[i][j]][id[i][k]] = (1.0 - p[k]) * p[i] / deg[k];
          for (i32 &k : e[i]) for (i32 &kk : e[j]) if (k != kk) f[id[i][j]][id[k][kk]] = (1.0 - p[k]) * (1.0 - p[kk]) / deg[k] / deg[kk];
        }   else {
          f[id[i][j]][id[i][j]] = (p[i] * p[j] - 1.0);
          for (i32 &k : e[i]) if (k != j) f[id[i][j]][id[k][j]] = (1.0 - p[k]) * p[j] / deg[k];
          for (i32 &k : e[j]) if (k != i) f[id[i][j]][id[i][k]] = (1.0 - p[k]) * p[i] / deg[k];
          for (i32 &k : e[i]) for (i32 &kk : e[j]) if (k != kk) f[id[i][j]][id[k][kk]] = (1.0 - p[k]) * (1.0 - p[kk]) / deg[k] / deg[kk];
        }
      }
    guass();
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%.10lf\n", ans[id[i][i]]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF113D::main(), 0; }
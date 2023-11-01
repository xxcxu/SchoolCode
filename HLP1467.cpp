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
namespace Solution_Of_HLP1467 {
  bool _1;
  static const i32 N = 100005, M = 2005;
  i32 n;
  i64 dep[N];
  i64 d[M][M];
  std::vector<std::pair<i32, i32>> e[N];
  bool _2;
  void dfs(i32 x, i32 fa, i64 *d) {
    for (auto &[y, z] : e[x])
      if (y != fa) {
        d[y] = d[x] + z;
        dfs(y, x, d);
      }
    return void();
  }
  bool check() {
    for (i32 x = 1; x <= n; ++x)
      for (auto &[y, z] : e[x])
        if (y != x - 1 && y != x + 1)
          return false;
    return true;
  }
  void dfs1(i32 x, i32 fa) {
    for (auto &[y, z] : e[x])
      if (y != fa) {
        dep[y] = dep[x] + z;
        dfs1(y, x);
      }
    return void();
  };
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("meet.in", "r");
    fout = fopen("meet.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].eb(v, w), e[v].eb(u, w);
    }
    i64 Start_Time_Without_Read = clock();
    if (check()) {
      i32 mid = (n + 1) / 2;
      i32 lpos = (mid + 1) / 2;
      i32 rpos = (mid + n + 1) / 2;
      i64 ans = 0;
      dfs1(1, 0);
      for (i32 i = 1; i <= n; ++i)
        ans += std::min(std::abs(dep[i] - dep[lpos]), std::abs(dep[i] - dep[rpos]));
      fprintf(fout, "%lld\n", ans);
      return void();
    }
    for (i32 i = 1; i <= n; ++i) dfs(i, 0, d[i]);
    i64 ans = LONG_LONG_MAX;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j) {
        i64 sum = 0;
        for (i32 k = 1; k <= n; ++k) sum += std::min(d[k][i], d[k][j]);
        ans = std::min(ans, sum);
      }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1467::main(), 0; }
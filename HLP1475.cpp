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
namespace Solution_Of_HLP1475 {
  bool _1;
  static const i32 N = 200005, P = 1000000007;
  i32 n, a[N];
  long double f[N][2];
  i32 g[N][2];
  std::vector<i32> e[N];
  bool _2;
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void dfs(i32 x, i32 fa) {
    f[x][1] = std::log(a[x]);
    f[x][0] = 0.0;
    g[x][1] = a[x];
    g[x][0] = 1;
    for (i32 y : e[x])
      if (y != fa) {
        dfs(y, x);
        if (f[y][1] > f[y][0]) f[x][0] += f[y][1], g[x][0] = mul(g[x][0], g[y][1]);
        else f[x][0] += f[y][0], g[x][0] = mul(g[x][0], g[y][0]);
        f[x][1] += f[y][0];
        g[x][1] = mul(g[x][1], g[y][0]);
      }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("water.in", "r");
    fout = fopen("water.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    i64 Start_Time_Without_Read = clock();
    dfs(1, 0);
    fprintf(fout, "%d\n", f[1][0] > f[1][1] ? g[1][0] : g[1][1]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1475::main(), 0; }
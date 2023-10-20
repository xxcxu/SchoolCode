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
namespace Solution_Of_HLP1441 {
  bool _1;
  using Node = std::pair<i32, i32>;
  static const i32 N = 1000005;
  i32 n, m, q;
  i32 a[N], d[25][25];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("andgraph.in", "r");
    fout = fopen("andgraph.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read(), q = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    std::memset(d, 0x3f, sizeof d);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 20; j >= 0; --j)
        if (a[i] >> j & 1)
          for (i32 k = 20; k >= 0; --k)
            if (a[i] >> k & 1) {
              chkmin(d[j][k], 2 * a[i]); 
              chkmin(d[k][j], 2 * a[i]);
            }
    for (i32 i = 0; i <= 20; ++i)
      for (i32 j = 0; j <= 20; ++j)
        for (i32 k = 0; k <= 20; ++k)
          chkmin(d[i][j], d[i][k] + d[k][j]);
    for (i32 i = 1; i <= q; ++i) {
      static i32 u, v;
      u = read(), v = read();
      if (a[u] & a[v])
        fprintf(fout, "%d\n", a[u] + a[v]);
      else {
        i32 ans = 0x3f3f3f3f;
        for (i32 j = 0; j <= 20; ++j)
          if (a[u] >> j & 1)
            for (i32 k = 0; k <= 20; ++k)
              if (a[v] >> k & 1)
                chkmin(ans, a[u] + a[v] + d[j][k]);
        fprintf(fout, "%d\n", ans == 0x3f3f3f3f ? -1 : ans);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1441::main(), 0; }
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
namespace Solution_Of_HLP1477 {
  bool _1;
  static const i32 N = 100005, BB = 325;
  i32 L, R, n, P, B;
  i32 f[N][BB], g[N][BB], h[N], sf[N][BB], sg[N][BB];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 calc(i32 x) {
    if (x <= B) {
      i32 res = 0;
      for (i32 i = x; i <= B; ++i)
        res = inc(res, f[n][i]);
      return inc(res, h[n]);
    } else {
      i32 res = 0;
      for (i32 i = 1; i <= n / x; ++i)
        if (n - i * (x - 1) >= 0) res = inc(res, g[n - i * (x - 1)][i]);
      return res;
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("fans.in", "r");
    fout = fopen("fans.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    L = read(), R = read(), n = read(), P = read();
    i64 Start_Time_Without_Read = clock();
    B = std::sqrt(n);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= std::min(i, B); ++j) {
        if (i == j) {
          f[i][j] = g[i][j] = 1;
        } else {
          i32 max = std::min(i - j, B), min = std::min(i - j, j - 1);
          f[i][j] = inc(dec(sf[i - j][max], sf[i - j][min]), h[i - j]);
          g[i][j] = sg[i - j][std::min(i - j, j)];
        }
        sf[i][j] = inc(sf[i][j - 1], f[i][j]);
        sg[i][j] = inc(sg[i][j - 1], g[i][j]);
        if (i + j * B <= n) h[i + j * B] = inc(h[i + j * B], g[i][j]);
      }
    fprintf(fout, "%d\n", dec(calc(L), calc(R + 1)));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1477::main(), 0; }
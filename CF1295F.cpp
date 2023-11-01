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
i64 read() {
  i64 t = 0, f = 0;
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
namespace Solution_Of_CF1295F {
  bool _1;
  static const i32 N = 55;
  static const i32 P = 998244353;
  i32 n;
  i64 l[N], r[N], a[N * 2];
  i32 f[N][N * 2];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 binom(i64 n, i32 m) {
    if (n < m || m < 0) return 0;
    i32 ans = 1;
    for (i64 i = n; i > n - m; --i) ans = mul(ans, i % P);
    for (i32 i = 1; i <= m; ++i) ans = mul(ans, qpow(i, P - 2));
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      l[i] = read(), r[i] = read() + 1;
      a[i * 2 - 1] = l[i], a[i * 2] = r[i];
    }
    i64 Start_Time_Without_Read = clock();
    std::sort(a + 1, a + 2 * n + 1);
    i32 m = std::unique(a + 1, a + 2 * n + 1) - a - 1;
    for (i32 i = 1; i <= n; ++i) l[i] = std::lower_bound(a + 1, a + m + 1, l[i]) - a;
    for (i32 i = 1; i <= n; ++i) r[i] = std::lower_bound(a + 1, a + m + 1, r[i]) - a;
    f[0][m] = 1;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j < m; ++j)
        for (i32 k = i - 1; k >= 0; --k) {
          if (!(l[k + 1] <= j && j + 1 <= r[k + 1])) break;
          i32 now = 0;
          for (i32 p = j + 1; p <= m; ++p) now = inc(now, f[k][p]);
          now = mul(now, binom(a[j + 1] - a[j] - 1 + (i - k), i - k));
          f[i][j] = inc(f[i][j], now);
        }
    i32 ans = 0;
    for (i32 i = 1; i < m; ++i) ans = inc(ans, f[n][i]);
    for (i32 i = 1; i <= n; ++i) ans = mul(ans, qpow((a[r[i]] - a[l[i]]) % P, P - 2));
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1295F::main(), 0; }
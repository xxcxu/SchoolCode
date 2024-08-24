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
namespace Solution_Of_CF1784D {
  bool _1;
  static const i32 N = 22;
  static const i32 P = 998244353;
  i32 n;
  i32 fac[1 << N], f[N][1 << N];
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
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    fac[0] = 1;
    for (i32 i = 1; i <= (1 << n); ++i) fac[i] = mul(fac[i - 1], i);
    f[0][0] = 1;
    for (i32 i = 0; i <= n; ++i)
      for (i32 j = (1 << n); j >= 0; --j) {
        if (j) f[i][j - 1] = inc(f[i][j - 1], mul(f[i][j], j));
        if (i < n) f[i + 1][j + (1 << (n - i - 1)) - 1] = inc(f[i + 1][j + (1 << (n - i - 1)) - 1], mul(f[i][j], 1 << (n - i - 1)));
      }
    for (i32 i = 1; i <= (1 << n); ++i)
      fprintf(fout, "%d\n", mul(mul(fac[(1 << n) - i], 1 << n), f[n][(1 << n) - i]));
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1784D::main(), 0; }
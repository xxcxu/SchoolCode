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
namespace Solution_Of_HLP1617 {
  bool _1;
  static const i32 N = 305;
  static const i32 P = 998244353;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
      i32 ans = 1;
      for (; y; y >>= 1, x = mul(x, x))
          if (y & 1) ans = mul(ans, x);
      return ans;
  }
  i32 n;
  i32 f[N], num[N][N];
  bool _2;
  i32 fac[N], inv[N];
  void init(i32 n) {
    fac[0] = 1;
    for (i32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (i32 i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
  }
  i32 binom(i32 n, i32 m) {
    if (n < m || m < 0) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("guess.in", "r");
    fout = fopen("guess.out", "w");
    n = read();
    init(N - 1);
    num[0][0] = 1;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 2 * i; j <= n; ++j) {
        for (i32 k = 2; k <= j; ++k) num[i][j] = inc(num[i][j], mul(num[i - 1][j - k], qpow(2, binom(k - 1, 2))));
      }
    for (i32 i = 1; i <= n; ++i) {
      f[i] = 0;
      for (i32 k = 1; k <= i; ++k) {
        for (i32 l = 2 * k; l <= i; ++l) {
          f[i] = inc(f[i], mul(f[i - l + k], mul(binom(i - l + k, k), num[k][l])));
        }
      }
      f[i] = dec(qpow(2, binom(i + 1, 2)), f[i]);
    }
    fprintf(fout, "%d\n", f[n]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1617::main(), 0; }
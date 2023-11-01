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
namespace Solution_Of_CF1842H {
  bool _1;
  static const i32 N = 20;
  static const i32 P = 998244353;
  i32 n, m;
  i32 a[N][2], f[1 << N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); } 
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 op, u, v;
      op = read();
      u = read() - 1, v = read() - 1;
      a[u][op] |= 1u << v, a[v][op] |= 1u << u;
    }
    i64 Start_Time_Without_Read = clock();
    f[0] = 1;
    for (i32 S = 0; S < (1 << n); ++S)
      for (i32 i = 0; i < n; ++i)
        if (S >> i & 1)
          for (i32 j = 0; j < 2; ++j)
            if (!(a[i][j ^ 1] & S))
              f[S] = inc(f[S], f[S ^ (1u << i)]);
    i32 ans = f[(1u << n) - 1];
    for (i32 i = 1; i <= n; ++i)
      ans = mul(ans, qpow(i, P - 2));
    ans = mul(ans, qpow(1 << n, P - 2));
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1842H::main(), 0; }
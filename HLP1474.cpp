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
namespace Solution_Of_HLP1474 {
  bool _1;
  static const i32 N = 16;
  static const i32 P = 1000000007;
  i32 n, m;
  i32 a[N];
  i32 g[1 << N], h[1 << N], f[1 << N];
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
  i32 get_inv(i32 x) { return qpow(x, P - 2); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("partition.in", "r");
    fout = fopen("partition.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 0; i < n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 S = 1; S < (1 << n); ++S) g[S] = g[S ^ (S & -S)] ^ a[(i32)log2(S & -S)];
    for (i32 S = 0; S < (1 << n); ++S) g[S] = inc(g[S], 1);
    for (i32 S = 1; S < (1 << n); ++S) {
      h[S] = g[S];
      for (i32 mask = (S ^ (S & -S)); ; mask = (mask - 1) & (S ^ (S & -S))) {
        i32 T = mask | (S & -S);
        if (T != S) h[S] = dec(h[S], mul(h[T], g[S ^ T]));
        if (!mask) break;
      }
    }
    f[0] = 1;
    for (i32 S = 1; S < (1 << n); ++S) {
      for (i32 mask = S ^ (S & -S); ; mask = (mask - 1) & (S ^ (S & -S))) {
        i32 T = mask | (S & -S);
        f[S] = inc(f[S], mul(m, mul(h[T], f[S ^ T])));
        if (!mask) break;
      }
    }
    fprintf(fout, "%d\n", f[(1 << n) - 1]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1474::main(), 0; }
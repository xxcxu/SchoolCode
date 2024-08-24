#pragma GCC optimize(2)
#pragma region
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
#pragma endregion
namespace Solution_Of_CF1530F {
  bool _1;
  static const i32 N = 21;
  static const i32 P = 31607;
  i32 n, ans;
  i32 p[N][N], g[N][1 << N], f[1 << N], cnt[1 << N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return x * y % P; }
  i32 qpow(i32 x, i32 y) {
      i32 ans = 1;
      for (; y; y >>= 1, x = mul(x, x))
          if (y & 1) ans = mul(ans, x);
      return ans;
  }
  i32 inv(i32 x) { return qpow(x, P - 2); }
  i32 lowbit(i32 x) { return x & -x; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i < (1 << n); ++i)
      cnt[i] = cnt[i ^ lowbit(i)] + 1;
    for (i32 i = 0; i < n; ++i) {
      g[i][0] = 1;
      for (i32 j = 0; j < n; ++j) {
        g[i][1 << j] = mul(read(), inv(10000));
      for (i32 j = 1; j < (1 << n); ++j)
        g[i][j] = mul(g[i][j ^ lowbit(j)], g[i][lowbit(j)]);
      }
    }
    for (i32 d = 0; d < 4; ++d) {
      for (i32 i = 0; i < (1 << n); ++i)
        if ((cnt[i] + cnt[d]) & 1) f[i] = P - 1;
        else f[i] = 1;
      for (i32 i = 0; i < n; ++i)
        for (i32 j = 0; j < (1 << n); ++j) {
          i32 mask = j;
          if (d >> 0 & 1) mask |= (1 << i);
          if (d >> 1 & 1) mask |= (1 << (n - i - 1));
          f[j] = mul(f[j], dec(g[i][mask], g[i][(1 << n) - 1]));
        }
      for (i32 i = 0; i < (1 << n); ++i)
        ans = inc(ans, f[i]);
    }
    fprintf(fout, "%d\n", dec(1, ans));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1530F::main(), 0; }
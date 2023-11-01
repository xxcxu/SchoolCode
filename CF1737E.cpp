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
namespace Solution_Of_CF1737E {
  bool _1;
  static const i32 N = 1000005;
  static const i32 P = 1000000007;
  i32 n, f[N], sum[N], fpow2[N];
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
  i32 sumf(i32 l, i32 r) {
    if (l > r) return 0;
    return sum[l] - sum[r + 1];
  }
  void solve() {
    n = read();
    sum[n + 1] = 0;
    f[n] = 1, sum[n] = 1;
    for (i32 i = n - 1; i >= 1; --i) {
      // i/2+1 ~ i
      i32 l = i + 1, r = std::min(2 * i - 1, n);
      f[i] = dec(sum[l], sum[r + 1]);
      sum[i] = inc(sum[i + 1], f[i]);
    }
    for (i32 i = 1; i <= n; ++i)
      fprintf(fout, "%d\n", mul(f[i], qpow(fpow2[n - i / 2 - 1], P - 2)));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fpow2[0] = 1;
    for (i32 i = 1; i < N; ++i)
      fpow2[i] = mul(fpow2[i - 1], 2);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1737E::main(), 0; }
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
namespace Solution_Of_CF1656F {
  bool _1;
  static const i32 N = 200005;
  i32 n, a[N];
  i64 sum[N];
  bool _2;
  i64 calc(i32 x, i32 t) {
    return 
    1ll * a[n] * (sum[x] - a[1]) +
    1ll * t * (1ll * (x - 1) * a[n] + (sum[x] - a[1])) +
    1ll * a[1] * (sum[n] - sum[x]) + 
    1ll * t * (1ll * (n - x) * a[1] + (sum[n] - sum[x]));
  }
  void solve() {
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    std::sort(a + 1, a + n + 1);
    for (i32 i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    if (1ll * (n - 1) * a[1] + (sum[n] - a[1]) > 0) return fputs("INF\n", fout), void();
    if (1ll * (n - 1) * a[n] + (sum[n] - a[n]) < 0) return fputs("INF\n", fout), void();
    i64 ans = LONG_LONG_MIN;
    for (i32 i = 1; i <= n; ++i)
      ans = std::max(ans, calc(i, -a[i]));
    fprintf(fout, "%lld\n", ans);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1656F::main(), 0; }
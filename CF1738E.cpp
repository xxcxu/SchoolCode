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
namespace Solution_Of_CF1738E {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 998244353;
  i32 n;
  i32 a[N];
  i64 pre[N], suf[N];
  i32 fac[N], inv[N], pow2[N];
  std::map<i64, i32> min, max;
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
  i32 binom(i32 n, i32 m) {
    if (n < m || m < 0) return 0;
    return mul(mul(fac[n], inv[m]), inv[n - m]);
  }
  void solve() {
    min.clear(), max.clear();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    pre[0] = suf[n + 1] = a[n + 1] = 0;
    for (i32 i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];
    for (i32 i = n; i >= 1; --i) suf[i] = suf[i + 1] + a[i + 1];
    i32 l = 1, r = n - 1;
    i32 ans = 1;
    while (l <= r) {
      if (pre[l] < suf[r]) { ++l; continue; }
      if (pre[l] > suf[r]) { --r; continue; }
      if (l > r) break;
      if (pre[l] == pre[r]) {
        ans = mul(ans, qpow(2, r - l + 1));
        break;
      }
      i32 L = l, R = r;
      while (pre[l] == pre[L + 1]) ++L;
      while (suf[r] == suf[R - 1]) --R;
      i32 coef = 0;
      i32 len1 = L - l + 1, len2 = r - R + 1;
      for (i32 i = 0; i <= len1 && i <= len2; ++i)
        coef = inc(coef, mul(binom(len1, i), binom(len2, i)));
      ans = mul(ans, coef);
      l = L + 1, r = R - 1;
    }
    fprintf(fout, "%d\n", ans);
    return void();
  }
  void init(i32 n) {
    fac[0] = 1;
    for (i32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (i32 i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    pow2[0] = 1;
    for (i32 i = 1; i <= n; ++i) pow2[i] = mul(pow2[i - 1], 2);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    init(N - 1);
    i32 t = read();
    while (t--) solve();
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1738E::main(), 0; }
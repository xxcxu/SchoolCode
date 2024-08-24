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
namespace Solution_Of_CF1749D {
  bool _1;
  static const i32 N = 300005;
  static const i32 P = 998244353;
  i32 n, all, ans, f[N];
  i64 m, g[N];
  i32 prime[N], cnt, vis[N];
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
  i32 inv(i32 x) { return qpow(x, P - 2); }
  void init(i32 n) {
    vis[1] = true;
    for (i32 i = 2; i <= n; ++i) {
      if (!vis[i]) prime[++cnt] = i;
      for (i32 j = 1; i * prime[j] <= n; ++j) {
        vis[i * prime[j]] = true;
        if (i % prime[j] == 0) break;
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    init(n);
    g[0] = f[0] = all = 1;
    for (i32 i = 1; i <= n; ++i) {
      g[i] = g[i - 1];
      if (!vis[i]) g[i] *= i;
      if (g[i] > m) g[i] = m + 1;
      f[i] = mul(f[i - 1], (m / g[i]) % P);
      all = mul(all, m % P);
      ans = inc(ans, dec(all, f[i]));
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1749D::main(), 0; }
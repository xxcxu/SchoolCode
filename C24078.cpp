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
namespace Solution_Of_C24078 {
  bool _1;
  static const i32 N = 5005, P = 998244353;
  i32 n, k;
  i32 mem[N], a[N], c[N][N], r[N], ir[N];
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
    c[0][0] = 1;
    for (i32 i = 1; i <= n; ++i) {
      c[i][0] = c[i][i] = 1;
      for (i32 j = 1; j < i; ++j)
        c[i][j] = inc(c[i - 1][j], c[i - 1][j - 1]);
    }
    for (i32 i = 0; i <= n; ++i) r[i] = c[n][i];
    for (i32 i = 1; i <= n; i += 2) r[i] = (P - r[i]) % P;
    for (i32 i = 0; i <= n; ++i) ir[i] = inv(r[i]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), k = read() + 1;
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    if (n <= k + 1) { return fputs("YES\n", fout), void(); }
    for (i32 i = 1; i <= k; ++i) {
      --n;
      for (i32 j = 1; j <= n; ++j)
        a[j] = dec(a[j + 1], a[j]);
    }
    i32 cnt = 0;
    for (i32 i = 1; i <= n; ++i) if (a[i]) ++cnt;
    if (cnt == 0) { return fputs("YES\n", fout), void(); }
    init(k);
    for (i32 p = -k; p <= n; ++p) {
      i32 mod = -1;
      bool flag = true;
      for (i32 i = 0; i <= k; ++i) {
        if (1 <= p + i && p + i <= n) {
          i32 m = mul(a[p + i], ir[i]);
          if (mod != -1) { if (mod != m) { flag = false; break; } }
          else { mod = m; }
        }
      }
      for (i32 i = 1; i < p; ++i) if (a[i]) flag = false;
      for (i32 i = p + k + 1; i <= n; ++i) if (a[i]) flag = false;
      if (flag) { return fputs("YES\n", fout), void(); }
    }
    fputs("NO\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_C24078::main(), 0; }
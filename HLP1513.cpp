#pragma GCC optimize(3)
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
namespace Solution_Of_HLP1513 {
  bool _1;
  static const i32 N = 1005;
  i32 n, m, q, phi, P, Q = 147744151;
  i32 a[N][N], sum[N][N], s[N][N], is[N][N], fpow[N * N];
  i32 sx[N * N * 2], sy[N * N * 2], tx[N * N * 2], ty[N * N * 2];
  i32 ans[N * N * 2];
  bool vis[N][N];
  std::vector<i32> factor;
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  i32 qpow(i32 x, i32 y) {
    if (y <= 100000) return fpow[y];
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans % P;
  }
  void exgcd(i32 a, i32 b, i64 &x, i64 &y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, x, y);
    i64 tmp = x;
    x = y, y = tmp - y * (a / b);
    return void();
  }
  i32 find(i32 x) {
    i32 p = x, res = x;
    for (i32 i = 2; i * i <= x; ++i)
      if (p % i == 0) {
        res = res - res / i;
        while (p % i == 0) p /= i;
      }
    if (p > 1) res = res - res / p;
    return res;
  }
  i32 qpow2(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 inv(i32 x) {
    return qpow2(x, phi - 1);
  }
  i32 query_m(i32 x, i32 y, i32 xx, i32 yy) {
    return mul(s[xx][yy], is[x - 1][yy], is[xx][y - 1], s[x - 1][y - 1]);
  }
  i32 query_s(i32 x, i32 y, i32 xx, i32 yy) {
    return sum[xx][yy] - sum[x - 1][yy] - sum[xx][y - 1] + sum[x - 1][y - 1];
  }
  void solve(i32 p) {
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        i32 cnt = 0;
        while (a[i][j] % p == 0) a[i][j] /= p, ++cnt;
        sum[i][j] = - sum[i - 1][j - 1] + sum[i][j - 1] + sum[i - 1][j] + cnt;
      }
    fpow[0] = 1;
    for (i32 i = 1; i <= 100000; ++i) fpow[i] = mul(fpow[i - 1], p);
    for (i32 i = 1; i <= q; ++i) ans[i] = mul(ans[i], qpow(p, query_s(sx[i], sy[i], tx[i], ty[i])));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tsuki.in", "r");
    fout = fopen("tsuki.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), P = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j)
        a[i][j] = read(); 
    i32 p = P;
    for (i32 i = 2; i * i <= p; ++i)
      if (p % i == 0) {
        while (p % i == 0) p /= i;
        factor.eb(i);
      }
    if (p != 1) factor.eb(p);
    phi = find(P);
    q = read();
    for (i32 i = 1; i <= q; ++i) {
      sx[i] = read(), sy[i] = read(), tx[i] = read(), ty[i] = read();
      ans[i] = 1;
    }
    for (i32 i : factor) solve(i);
    s[0][0] = 1, is[0][0] = 1;
    for (i32 i = 1; i <= m; ++i) s[0][i] = 1, is[0][i] = 1;
    for (i32 i = 1; i <= n; ++i) s[i][0] = 1, is[i][0] = 1;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        s[i][j] = a[i][j];
        if (i > 1 && j > 1) s[i][j] = mul(s[i][j], inv(s[i - 1][j - 1]));
        if (i > 1) s[i][j] = mul(s[i][j], s[i - 1][j]);
        if (j > 1) s[i][j] = mul(s[i][j], s[i][j - 1]);
        is[i][j] = inv(s[i][j]);
      }
    for (i32 i = 1; i <= q; ++i) ans[i] = mul(ans[i], query_m(sx[i], sy[i], tx[i], ty[i]));
    i64 res = 0;
    for (i32 i = 1; i <= q; ++i) res = (res + (i xor ans[i])) % Q;
    fprintf(fout, "%lld\n", res);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1513::main(), 0; }
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
template<typename T>
T read() {
  T t = 0, f = 0;
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
namespace Solution_Of_HLP1476 {
  bool _1;
  static const i32 N = 5005;
  static const i32 P = 10000019;
  i64 n; i32 q;
  i64 cnt[N];
  i32 fac[P], inv[P];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i64 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  } 
  void init(i32 n) {
    fac[0] = 1;
    for (i32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (i32 i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
  }
  i32 binom(i64 n, i64 m) {
    if (n < m || m < 0) return 0;
    if (n >= P) return mul(binom(n % P, m % P), binom(n / P, m / P));
    return mul(mul(fac[n], inv[m]), inv[n - m]);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("simple.in", "r");
    fout = fopen("simple.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    init(P - 1);
    n = read<i64>(), q = read<i32>();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 0; (1LL << i) <= n; ++i)
      cnt[(i & 1) ^ 1] += (n / (1LL << i) + 1) / 2 - (n / (1LL << (i + 1)) + 1) / 2;
    while (q--) {
      static i64 m;
      m = read<i64>();
      m = 2 * m - n;  
      if (m < -cnt[1] || m > cnt[1] || (m + cnt[1]) & 1)
        fprintf(fout, "%d\n", 0);
      else
        fprintf(fout, "%d\n", mul(qpow(2, cnt[0]), binom(cnt[1], (m + cnt[1]) / 2)));
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1476::main(), 0; }
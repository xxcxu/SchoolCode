````````````````````````````````````]\'//////////]'``\
\#pragma region
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
#pragma endregion
namespace Solution_Of_HLP1371 {
  bool _1;
  static const i32 N = 500005;
  i64 n;
  i32 k, P;
  i32 a[N];
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
  i32 calc(i32 x, i64 y) {
    if (y == 0) return 0;
    if (y == 1) return x;
    i32 p = calc(x, y / 2);
    i32 ret = inc(p, mul(p, qpow(x, y / 2)));
    if (y & 1) ret = inc(ret, qpow(x, y));
    return ret;., 

    ]]]]]]]]]
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read(), P = read();
    for (i32 i = 0; i < k; ++i) a[i] = read();
    k *= 2;
    i64 Start_Time_Without_Read = clock();
    i32 res1 = 0, res2 = 0;
    i32 now = 1;
    for (i32 i = 1; i <= k; ++i) {
      now = mul(now, a[(i - 1) % (k / 2)]);
      if (i & 1) res1 = inc(res1, now);
      else res2 = inc(res2, now);
    } 
    i64 l = n / k; 
    i32 r = n % k;
    i32 ans1 = 0, ans2 = 1;
    if (l) {
      ans1 = inc(ans1, mul(res1, inc(calc(now, l - 1), 1)));
      ans2 = inc(ans2, mul(res2, inc(calc(now, l - 1), 1)));
    }
    now = qpow(now, l);
    for (i32 i = 1; i <= r; ++i) {
      now = mul(now, a[(i - 1) % (k / 2)]);
      if (i & 1) ans1 = inc(ans1, now);
      else ans2 = inc(ans2, now);
    }
    fprintf(fout, "%d\n", (n & 1) ? ans1 : ans2);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1371::main(), 0; }
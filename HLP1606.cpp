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
namespace Solution_Of_HLP1606 {
  bool _1;
  static const i32 N = 8005;
  i32 n, seed;
  bool edge[N][N];
  bool _2;
  namespace GenHelper {
    u32 z1, z2, z3, z4, b, u;
    u32 get() {
      b = ((z1 << 6) ^ z1) >> 13;
      z1 = ((z1 & 4294967294U) << 18) ^ b;
      b = ((z2 << 2) ^ z2) >> 27;
      z2 = ((z2 & 4294967288U) << 2) ^ b;
      b = ((z3 << 13) ^ z3) >> 21;
      z3 = ((z3 & 4294967280U) << 7) ^ b;
      b = ((z4 << 3) ^ z4) >> 12;
      z4 = ((z4 & 4294967168U) << 13) ^ b;
      return (z1 ^ z2 ^ z3 ^ z4);
    }
    bool read() {
      while (!u) u = get();
      bool res = u & 1;
      u >>= 1;
      return res;
    }
    void srand(i32 x) {
      z1 = x;
      z2 = (~x) ^ 0x233333333U;
      z3 = x ^ 0x1234598766U;
      z4 = (~x) + 51;
      u = 0;
      return void();
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), seed = read();
    GenHelper::srand(seed);
    for (i32 i = 1; i <= n; ++i)
        for (i32 j = i + 1; j <= n; ++j)
            edge[j][i] = edge[i][j] = GenHelper::read();
    i64 ans = 0;
    for (i32 i = 1; i <= n; ++i) {
      i32 cnt = 0;
      for (i32 j = 1; j <= n; ++j)
        if (edge[i][j]) ++cnt;
      ans -= cnt * (n - cnt - 1);
    }
    ans /= 2;
    ans += 1LL * n * (n - 1) * (n - 2) / 6;
    fprintf(fout, "%lld\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1606 ::main(), 0; }
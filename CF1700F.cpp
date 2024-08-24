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
namespace Solution_Of_CF1700F {
  bool _1;
  static const i32 N = 200005;
  i32 n; i64 ans;
  i32 a[2][N], b[2][N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    i32 sa = 0, sb = 0;
    for (i32 i = 0; i < 2; ++i)
      for (i32 j = 1; j <= n; ++j)
        a[i][j] = read(), sa += a[i][j];
    for (i32 i = 0; i < 2; ++i)
      for (i32 j = 1; j <= n; ++j)
        b[i][j] = read(), sb += b[i][j];
    if (sa != sb) { return fputs("-1\n", fout), void(); }
    i32 s0 = 0, s1 = 0;
    for (i32 i = 1; i <= n; ++i) {
      s0 += a[0][i] - b[0][i], s1 += a[1][i] - b[1][i];
      if (s0 < 0 && s1 > 0) { i32 add = std::min(-s0, s1); ans += add; s0 += add; s1 -= add; }
      else if (s0 > 0 && s1 < 0) { i32 add = std::min(s0, -s1); ans += add; s1 += add; s0 -= add; }
      ans += std::abs(s0) + std::abs(s1);
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1700F::main(), 0; }
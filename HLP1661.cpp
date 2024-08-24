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
namespace Solution_Of_HLP1661 {
  bool _1;
  static const i32 N = 500005;
  i32 n, a[N];
  i64 ans;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("water.in", "r");
    fout = fopen("water.out", "w");
    n = read();
    for (i32 i = n; i >= 1; --i) {
      if (3 * i - 1 > n) a[i] = 0;
      else a[i] = a[3 * i - 1] + 1;
      ans += (2 * i - 1) * (1LL << a[i]);
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1661::main(), 0; }
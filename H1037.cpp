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
namespace Solution_Of_H1037 {
  bool _1;
  static const i32 N = 20;
  i32 n, m;
  i32 a[N * 2], sum[1 << N];
  bool _2;
  i32 lowbit(i32 x) { return x & -x; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    for (i32 i = 0; i < n * 2; ++i) a[i] = read();
    for (i32 i = 1; i < (1 << (n * 2)); ++i) {
      sum[i] = sum[i - lowbit(i)] + a[(i32)std::log2(lowbit(i))];
      if (sum[i] == m) {
        i32 cnt = 0;
        for (i32 j = 0; j < n * 2; ++j) if (i >> j & 1) ++cnt;
        fprintf(fout, "%d\n", cnt);
        for (i32 j = 0; j < n * 2; ++j) if (i >> j & 1) fprintf(fout, "%d ", j + 1);
        fputs("\n", fout);
        return void();
      }
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_H1037::main(), 0; }
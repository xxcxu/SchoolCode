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
namespace Solution_Of_ {
  bool _1;
  static const i32 N = 1e5 + 1;
  i32 n = 1e5;
  i32 f[N];
  bool _2;
  bool check(i32 n) {
    while (n) {
      if (!((1 <= (n % 10)) && ((n % 10) <= 3))) return false;
      n /= 10;
    }
    return true;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fout = fopen("philo.ans", "w");
    for (i32 i = 1; i <= n; ++i) if (check(i)) f[i] = 1;
    for (i32 i = 1; i <= n; ++i) if (!f[i]) {
      f[i] = 0x3f3f3f3f;
      for (i32 j = 1; j <= (i + 1) / 2; ++j)
        f[i] = std::min(f[i], f[j] + f[i - j]);
    }
    for (i32 i = 1; i <= 100000; ++i) fprintf(fout, "%d\n", f[i]); 
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }
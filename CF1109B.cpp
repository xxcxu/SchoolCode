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
namespace Solution_Of_CF1109B {
  bool _1;
  static const i32 N = 5005;
  i32 n;
  char s[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    if (n & 1) {
      bool flag = false;
      for (i32 i = 2; i * 2 <= n; ++i) if (s[i] != s[i - 1]) flag = true;
      if (!flag) { fputs("Impossible\n", fout); return void(); }
      fputs("2\n", fout);
    } else {
      bool flag = false;
      for (i32 i = 2; i * 2 <= n; ++i) if (s[i] != s[i - 1]) flag = true;
      if (!flag) { fputs("Impossible\n", fout); return void(); }
      flag = false;
      auto check = [&](i32 m) {
        for (i32 i = 1; i * 2 <= m; ++i)
          if (s[i] != s[m - i + 1]) return false;
        return true;
      };
      for (i32 i = n; (i % 2 == 0) && i > 0; i >>= 1) {
        if (!check(i / 2)) {
          flag = true;
          break;
        }
      }
      fputs(flag ? "1\n" : "2\n", fout);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1109B::main(), 0; }
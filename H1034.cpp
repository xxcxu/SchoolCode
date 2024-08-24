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
namespace Solution_Of_H1034 {
  bool _1;
  static const i32 N = 30005;
  i32 n, m, cnt;
  i32 a[N], b[N];
  char s[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    i32 T = read();
    if (T == 1) {
      n = read(), m = read();
      fscanf(fin, "%s", s + 1);
      for (i32 i = 1; i <= m; ++i) a[i] = read();
      for (i32 i = 1; i <= m; ++i) {
        i32 t = a[i] % 2000;
        i32 p = t / 26, q = t % 26;
        if (s[p] == 'a' + q) b[++cnt] = a[i];
      }
      fprintf(fout, "%d\n", cnt);
      for (i32 i = 1; i <= cnt; ++i) fprintf(fout, "%d ", b[i]);
      fputs("\n", fout);
    } else {
      m = read();
      for (i32 i = 1; i <= m; ++i) {
        a[i] = read();
        i32 t = a[i] % 2000;
        i32 p = t / 26, q = t % 26;
        s[p] = 'a' + q;
      }
      n = strlen(s + 1);
      for (i32 i = 1; i <= n; ++i) fputc(s[i], fout);
      fputs("\n", fout);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_H1034::main(), 0; }
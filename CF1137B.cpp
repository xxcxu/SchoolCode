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
namespace Solution_Of_CF1137B {
  bool _1;
  static const i32 N = 500005;
  i32 n, m;
  char s[N], t[N];
  i32 next[N];
  bool _2;
  void init() {
    for (i32 i = 2, j = 0; i <= m; ++i) {
      while (j && t[j + 1] != t[i]) j = next[j];
      if (t[j + 1] == t[i]) ++j;
      next[i] = j;
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fscanf(fin, "%s %s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    init();
    i32 cnt0, cnt1 = 0;
    for (i32 i = 1; i <= n; ++i) if (s[i] == '1') ++cnt1;
    cnt0 = n - cnt1;
    for (i32 i = 1, j = 1; i <= n; ++i, ++j) {
      if (t[j] == '1' && !cnt1) fputc('0', fout), --cnt0;
      else if (t[j] == '0' && !cnt0) fputc('1', fout), --cnt1;
      else {
        fputc(t[j], fout);
        if (t[j] == '0') --cnt0;
        else --cnt1;
      }
      if (j == m) j = next[j];
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1137B::main(), 0; }
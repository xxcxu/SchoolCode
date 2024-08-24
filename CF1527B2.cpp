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
namespace Solution_Of_CF1527B2 {
  bool _1;
  static const i32 N = 1005;
  i32 n;
  char s[N];
  bool _2;
  void solve() {
    n = read();
    fscanf(fin, "%s", s + 1);
    bool flag = true;
    for (i32 i = 1; i <= (n + 1) / 2; ++i)
      if (s[i] != s[n - i + 1]) flag = false;
    i32 cnt = 0;
    for (i32 i = 1; i <= n; ++i) if (s[i] == '0') ++cnt;
    if (flag) {
      if (cnt & 1) { fputs(cnt == 1 ? "BOB\n" : "ALICE\n", fout); }
      else fputs("BOB\n", fout);
    } else {
      if ((n & 1) && s[(n + 1) / 2] == '0' && cnt == 2) fputs("DRAW\n", fout);
      else fputs("ALICE\n", fout);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    i32 t = read();
    while (t--) solve();
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1527B2::main(), 0; }
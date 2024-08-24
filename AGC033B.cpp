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
namespace Solution_Of_AGC033B {
  bool _1;
  static const i32 N = 200005;
  i32 h, w, n, x, y, u, d, l, r;
  char s[N], t[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    h = read(), w = read(), n = read();
    x = read(), y = read();
    fscanf(fin, "%s%s", s + 1, t + 1);
    u = d = x, l = r = y;
    for (i32 i = 1; i <= n; ++i) {
      if (s[i] == 'U') --d; if (s[i] == 'D') ++u;
      if (s[i] == 'L') --r; if (s[i] == 'R') ++l;
      if (d < 1 || u > h || r < 1 || l > w) return fputs("NO\n", fout), void();
      if (t[i] == 'U') u = std::max(u - 1, 1); if (t[i] == 'D') d = std::min(d + 1, h);
      if (t[i] == 'L') l = std::max(l - 1, 1); if (t[i] == 'R') r = std::min(r + 1, w);
    }
    fputs("YES\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_AGC033B::main(), 0; }
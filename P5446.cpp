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
namespace Solution_Of_P5446 {
  bool _1;
  static const i32 N = 1000005;
  i32 n, m;
  i32 r[N];
  char s[N];
  bool vis[N];
  bool _2;
  void solve() {
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    s[0] = '$'; s[n + 1] = '#';
    i32 mx = 0, id = 0;
    for (i32 i = 1; i <= n; ++i) {
      r[i] = i < mx ? std::min(r[(id << 1) - i], mx - i) : 0;
      while (s[i - r[i] - 1] == s[i + r[i] + 1]) ++r[i];
      if (i + r[i] > mx) mx = i + r[i], id = i;
    }
    for (i32 i = 1; i <= n; ++i) vis[i] = 0;
    for (i32 i = n; i >= 1; --i) {
      if (i + r[i] == n) vis[i] = 1;
      if (vis[i + r[i]] && i - r[i] == 1) vis[i] = 1;
    }
    for (i32 i = 1; i <= n; ++i) if (vis[i]) fprintf(fout, "%d ", i);
    fputs("\n", fout);
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
signed main() { return Solution_Of_P5446::main(), 0; }
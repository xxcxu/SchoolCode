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
namespace Solution_Of_clash {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, p, q;
  std::vector<i32> e[N];
  i32 b[N], c[N], d[N], by[N];
  i32 maxr[N];
  bool _2;
  void dfs(i32 x, i32 s, i32 bel) {
    if (!by[x]) by[x] = bel;
    if (!s) return void();
    if (s <= maxr[x]) return void();
    maxr[x] = std::max(maxr[x], s);
    for (auto &y : e[x]) dfs(y, s - 1, bel);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("clash.in", "r");
    fout = fopen("clash.out", "w");
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read(), p = read(), q = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    for (i32 i = 1; i <= q; ++i) b[i] = read(), c[i] = read(), d[i] = read();
    for (i32 i = q; i >= 1; --i) dfs(c[i], d[i], b[i]);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", by[i]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_clash::main(), 0; }
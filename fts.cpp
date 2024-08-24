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
  static const i32 N = 100005;
  i32 n, m, h0;
  i64 h[N], hh[N];
  bool vis[N];
  std::vector<std::pair<i32, i32>> e[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fin = fopen("fts.in", "r");
    fout = fopen("fts.out", "w");
    i64 Start_Time = clock();
    n = read(), m = read(), h0 = read();
    for (i32 i = 1; i <= n; ++i) h[i] = read();
    for (i32 i = 1; i <= m; ++i) {  
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].eb(v, w);
      e[v].eb(u, w);
    }
    std::priority_queue<std::pair<i64, i32>> q;
    for (i32 i = 1; i <= n; ++i) hh[i] = -0x3f3f3f3f3f3f3f3f;
    hh[1] = h0;
    q.ep((i64)h0, 1);
    while (q.size()) {
      i32 x = q.top().second; q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto &[y, z] : e[x]) {
        if (h[x] >= z) {
          i64 t = std::min(hh[x] - z, h[y]);
          if (chkmax(hh[y], t)) q.ep(hh[y], y);
        }
      }
    }
    if (!vis[n]) fputs("-1\n", fout);
    else {
      i64 ans = 0;
      ans += h0 - hh[n]; // jump
      ans += h[n] - hh[n]; // top
      fprintf(fout, "%lld\n", ans);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }
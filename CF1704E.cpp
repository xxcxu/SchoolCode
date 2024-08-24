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
namespace Solution_Of_CF1704E {
  bool _1;
  static const i32 N = 1005;
  static const i32 P = 998244353;
  i32 n, m;
  i32 in[N];
  i64 a[N];
  i32 ord[N], tot;
  std::vector<i32> e[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  void solve() {
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) e[i].clear();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v); ++in[v];
    }
    std::queue<i32> q;
    for (i32 i = 1; i <= n; ++i) if (!in[i]) q.ep(i);
    tot = 0;
    while (q.size()) {
      i32 x = q.front(); q.pop();
      ord[++tot] = x;
      for (auto &y : e[x])
        if (!(--in[y])) q.ep(y);
    }
    for (i32 i = 1; i <= n; ++i) {
      std::vector<i32> v;
      for (i32 j = 1; j <= n; ++j) if (a[j]) v.eb(j);
      if (v.empty()) { fprintf(fout, "%d\n", i - 1); return void(); }
      for (auto &j : v) --a[j];
      for (auto &j : v) for (auto &k : e[j]) ++a[k];
    }
    for (i32 i = 1; i <= n; ++i)
      for (auto &j : e[ord[i]])
        a[j] = inc(a[j], a[ord[i]]);
    fprintf(fout, "%d\n", inc(a[ord[n]], n));
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
signed main() { return Solution_Of_CF1704E::main(), 0; }
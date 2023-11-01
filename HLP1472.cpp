#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
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
#pragma endregion
namespace Solution_Of_HLP1472 {
  bool _1;
  static const i32 N = 500005;
  i32 n;
  i32 a[N], f[N], g[N], mx1[N], mx2[N], mx3[N];
  std::vector<i32> e[N];
  bool _2;
  void ins(i32 &mx1, i32 &mx2, i32 &mx3, i32 v) {
    if (v >= mx1) mx3 = mx2, mx2 = mx1, mx1 = v;
    else if (v >= mx2) mx3 = mx2, mx2 = v;
    else chkmax(mx3, v);
    return void();
  }
  void del(i32 &mx1, i32 &mx2, i32 &mx3, i32 v) {
    if (v < mx3) return void();
    if (v < mx2) return mx3 = 0, void();
    if (v < mx1) return mx2 = mx3, mx3 = 0, void();
    return mx1 = mx2, mx2 = mx3, mx3 = 0, void();
  }
  void dfs(i32 x, i32 fa) {
    f[x] = a[x];
    for (i32 y : e[x])
      if (y != fa) {
        dfs(y, x);
        ins(mx1[x], mx2[x], mx3[x], f[y]);
      }
    if (fa != 0) f[x] = std::max(f[x], mx2[x]);
    else f[x] = std::max(f[x], mx1[x]);
    return void();
  }
  void dfs2(i32 x, i32 fa) {
    for (i32 y : e[x])
      if (y != fa) {
        del(mx1[x], mx2[x], mx3[x], f[y]);
        ins(mx1[y], mx2[y], mx3[y], std::max(a[x], mx2[x]));
        ins(mx1[x], mx2[x], mx3[x], f[y]);
        g[y] = std::max(a[y], mx1[y]);
        dfs2(y, x);
      }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tree.in", "r");
    fout = fopen("tree.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    i64 Start_Time_Without_Read = clock();
    dfs(1, 0);
    g[1] = f[1];
    dfs2(1, 0);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d ", g[i]);
    fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1472::main(), 0; }
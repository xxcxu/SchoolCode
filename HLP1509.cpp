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
namespace Solution_Of_HLP1509 {
  bool _1;
  static const i32 N = 205;
  i32 n;
  i32 u[N], v[N], dep[N], max[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    for (i32 y : e[x])
      if (y != fa) {
        dep[y] = dep[x] + 1;
        dfs(y, x);
      }
    max[dep[x]] = std::max(max[dep[x]], (i32)std::size(e[x]) - (fa != 0)); 
    return void();
  }
  void solve() {
    n = read();
    if (n == 0) return fputs("0 0\n", fout), void();
    for (i32 i = 1; i <= n; ++i) e[i].clear();
    for (i32 i = 1; i < n; ++i) {
      u[i] = read(), v[i] = read();
      e[u[i]].eb(v[i]), e[v[i]].eb(u[i]);
    }
    i32 ans1 = n + 1; i64 ans2 = -1;
    auto update = [&](i32 x, i64 y) {
      if (x < ans1 || (x == ans1 && y < ans2))
        ans1 = x, ans2 = y;
      return void();
    };
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j = 1; j <= n; ++j) max[j] = 0;
      dep[i] = 1;
      dfs(i, 0);
      i64 leaf = 1; i32 len = 1;
      for (; max[len]; ++len);
      for (i32 j = 1; j < len; ++j) leaf *= max[j];
      update(len, leaf);
    }
    for (i32 i = 1; i < n; ++i) {
      for (i32 j = 1; j <= n; ++j) max[j] = 0;
      dep[u[i]] = dep[v[i]] = 1;
      dfs(u[i], v[i]); dfs(v[i], u[i]);
      i64 leaf = 2; i32 len = 1;
      for (; max[len]; ++len);
      for (i32 j = 1; j < len; ++j) leaf *= max[j];
      update(len, leaf);
    }
    fprintf(fout, "%d %lld\n", ans1, ans2);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("plant.in", "r");
    fout = fopen("plant.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1509::main(), 0; }
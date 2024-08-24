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
namespace Solution_Of_HLP3671 {
  bool _1;
  static constexpr i32 N = 2000005;
  i32 n, m, ts;
  std::vector<i32> e[N], g[N], Graph[N];
  i32 L[N], R[N], s[N], fa[N];
  i64 ans;
  bool _2;
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void add(i32 x, i32 v) {
    for (; x <= ts; x += x & -x)
      s[x] += v;
    return void();
  }
  i32 ask(i32 x) {
    i32 ans = 0;
    for (; x >= 1; x -= x & -x)
      ans += s[x];
    return ans;
  }
  void init(i32 x, i32 fa) {
    L[x] = ++ts;
    for (i32 y : g[x])
      if (y != fa)
        init(y, x);
    R[x] = ts;
    return void();
  }
  void dfs(i32 x, i32 fa) {
    ans += ask(R[x]) - ask(L[x] - 1);
    add(L[x], 1);
    for (i32 y : e[x])
      if (y != fa)
        dfs(y, x);
    add(L[x], -1);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 2; i <= n; ++i) {
      i32 x = read();
      Graph[x].eb(i);
      Graph[i].eb(x);
    }
    for (i32 i = 1; i <= n; ++i) fa[i] = i;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j : Graph[i])
        if (i > j) {
          i32 f = find(j);
          if (i == f) continue;
          e[i].eb(f);
          fa[f] = i;
        }
    for (i32 i = 1; i <= n; ++i) fa[i] = i;
    for (i32 i = n; i >= 1; --i)
      for (i32 j : Graph[i])
        if (i < j) {
          i32 f = find(j);
          if (i == f) continue;
          g[i].eb(f);
          fa[f] = i;
        }
    init(1, 0);
    dfs(n, 0);
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP3671::main(), 0; }
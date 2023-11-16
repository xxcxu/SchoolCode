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
i32 read() {
  i32 t = 0, f = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
  for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_HLP138 {
  bool _1;
  static const i32 N = 1000005;
  i32 n, m, k, ts;
  i32 id[N], dep[N], fa[N], dfn[N];
  bool chg[N];
  std::vector<i32> g[N];
  using verge = std::pair<i32, i32>;
  std::vector<verge> e[N];
  using edge = std::tuple<i32, i32, i32>;
  std::vector<edge> edges;
  bool _2;
  void dfs(i32 x, i32 pre) {
    dep[x] = dep[pre] + 1;
    fa[x] = pre;
    for (auto &[y, z] : e[x]) {
      if (y == pre) continue;
      if (!dep[y]) id[y] = z, dfs(y, x);
      else if (dep[x] > dep[y]) edges.eb(x, y, z);
    }
    return void();
  }
  void dfs2(i32 x) {
    dfn[x] = ++ts;
    for (i32 y : g[x]) dfs2(y);
    return void();
  }
  void solve() {
    n = read(), m = read(), k = read();
    for (i32 i = 1; i <= n; ++i) e[i].clear();
    for (i32 i = 1; i <= n; ++i) dep[i] = 0;
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v, i), e[v].eb(u, i);
    }
    if (k > m - (n - 1)) return puts("-1"), void();
    edges.clear();
    dfs(1, 0);
    for (i32 i = 1; i <= n; ++i)
      if (!dep[i]) return puts("-1"), void();
    std::sort(all(edges), [&](const edge &x, const edge &y) {
      return std::make_pair(dep[std::get<0>(x)], dep[std::get<1>(x)]) > std::make_pair(dep[std::get<0>(y)], dep[std::get<1>(y)]);
    });
    for (i32 i = 0; i < m - (n - 1) - k; ++i) {
      auto &[x, y, z] = edges[i];
      fa[x] = y, id[x] = z;
    }
    for (i32 i = 1; i <= m; ++i) chg[i] = false;
    for (i32 i = 1; i <= n; ++i) g[i].clear();
    for (i32 i = 1; i <= n; ++i) g[fa[i]].eb(i), chg[id[i]] = true;
    ts = 0;
    dfs2(1);
    for (i32 i = 1; i <= n; ++i) printf("%d%c", dfn[i], " \n"[i == n]);
    for (i32 i = 1; i <= m; ++i) printf("%d%c", chg[i], " \n"[i == m]);
    return void();
  }
  void main() {
    freopen("admin.in", "r", stdin);
    freopen("admin.out", "w", stdout);
    i32 t = read(); n = read();
    while (t--) solve();
    return void();
  }
}
signed main() { return Solution_Of_HLP138::main(), 0; }
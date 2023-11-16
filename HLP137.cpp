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
namespace Solution_Of_HLP137 {
  bool _1;
  static const i32 N = 2000005;
  i32 n, m, k, tot;
  i32 a[N], b[N], d[N], ans[N], dep[N], anc[N][21], top[N], son[N], size[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    dep[x] = dep[fa] + 1;
    size[x] = 1;
    anc[x][0] = fa;
		for (i32 i = 1; i < 21; ++i) anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (i32 y : e[x]) if (y != fa) { dfs(y, x), size[x] += size[y]; if (size[y] > size[son[x]]) son[x] = y; }
    return void();
  }
  void dfs1(i32 x, i32 tp) {
    top[x] = tp;
    if (son[x]) dfs1(son[x], tp);
    for (i32 y : e[x])
      if (y != son[x] && y != anc[x][0])
        dfs1(y, y);
    return void();
  }
  i32 lca(i32 x, i32 y) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
      x = anc[top[x]][0];
    }
    return dep[x] < dep[y] ? x : y;
  }
  void change(i32 u, i32 v) {
    i32 l = lca(u, v);
    ++d[u], ++d[v];
    --d[l], --d[anc[l][0]];
    return void();
  }
  void dfs2(i32 x, i32 fa) {
    for (i32 y : e[x])
      if (y != fa) {
        dfs2(y, x);
        d[x] += d[y];
      }
    if (d[x] >= 1) a[x] = 0;
    return void();
  }
  void dfs3(i32 x, i32 fa) {
    for (i32 y : e[x])
      if (y != anc[x][0]) {
        b[y] = b[x] + a[y];
        dfs3(y, x);
      }
    return void();
  }
  i32 query(i32 u, i32 v) {
    i32 l = lca(u, v);
    i32 ans = b[u] + b[v] - b[l] - b[anc[l][0]];
    if (ans == 1) {
      if (b[u] - b[anc[l][0]] == 1) {
        for (i32 i = 20; i >= 0; --i)
          if (dep[anc[u][i]] >= dep[l] && b[anc[u][i]] - b[anc[l][0]] == 1)
            u = anc[u][i];
        return u;
      } else {
        for (i32 i = 20; i >= 0; --i)
          if (dep[anc[v][i]] >= dep[l] && b[anc[v][i]] - b[anc[l][0]] == 1)
            v = anc[v][i];
        return v;
      }
    } else return -1;
  }
  using qNode = std::tuple<i32, i32, i32>;
  std::vector<qNode> vec;
  void main() {
    freopen("werewolf.in", "r", stdin);
    freopen("werewolf.out", "w", stdout);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = 1;
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    for (i32 i = 1; i <= m; ++i) {
      static i32 l, r, op;
      l = read(), r = read(), op = read();
      vec.eb(op, l, r);
    }
    dfs(1, 0); dfs1(1, 1);
    for (auto [op, u, v] : vec) if (!op) change(u, v);
    dfs2(1, 0);
    b[1] = a[1];
    dfs3(1, 0);
    for (auto [op, u, v] : vec) if (op) {
      i32 p = query(u, v);
      if (p != -1) ans[p] = true;
    }
    i32 cnt = 0;
    for (i32 i = 1; i <= n; ++i) if (ans[i]) ++cnt;
    printf("%d\n", cnt);
    for (i32 i = 1; i <= n; ++i) if (ans[i]) printf("%d ", i);
    puts("");
    return void();
  }
}
signed main() { return Solution_Of_HLP137::main(), 0; }
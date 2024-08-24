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
namespace Solution_Of_P4556 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, cnt;
  i32 rt[N], dep[N], anc[N][22];
  i32 ans[N];
  std::vector<i32> e[N];
  bool _2;
  struct TreeNode {
    i32 p, max;
    TreeNode(i32 p = 0, i32 max = 0):
      p(p), max(max) {}
  } tr[N * 80];
  i32 ls[N * 80], rs[N * 80];
  void dfs(i32 x, i32 fa) {
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &y : e[x])
      if (y != fa) {
        dfs(y, x);
      }
    return void();
  }
  i32 lca(i32 x, i32 y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 21; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y])
        x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 21; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  void pushup(i32 x) {
    i32 pv = tr[ls[x]].max, qv = tr[rs[x]].max;
    if (pv == 0) tr[x] = tr[rs[x]];
    else if (qv == 0) tr[x] = tr[ls[x]];
    else if (pv >= qv) tr[x] = tr[ls[x]];
    else tr[x] = tr[rs[x]];
    return void();
  }
  void modify(i32 &x, i32 l, i32 r, i32 p, i32 v) {
    if (!x) x = ++cnt;
    if (l == r) {
      tr[x].max += v;
      tr[x].p = l;
      return void();
    }
    i32 mid((l + r) >> 1);
    if (p <= mid) modify(ls[x], l, mid, p, v);
    else modify(rs[x], mid + 1, r, p, v);
    return pushup(x);
  }
  i32 merge(i32 x, i32 y, i32 l, i32 r) {
    if (!x || !y) return x + y;
    if (l == r) {
      tr[x].max += tr[y].max;
      return x;
    }
    i32 mid((l + r) >> 1);
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid + 1, r);
    pushup(x);
    return x;
  }
  void dfs2(i32 x, i32 fa) {
    for (auto &y : e[x])
      if (y != fa) {
        dfs2(y, x);
        rt[x] = merge(rt[x], rt[y], 1, 100000);
      }
    ans[x] = tr[rt[x]].p;
    if (tr[rt[x]].max == 0) ans[x] = 0;
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 0);
    for (i32 i = 1; i <= m; ++i) {
      static i32 x, y, z;
      x = read(), y = read(), z = read();
      modify(rt[x], 1, 100000, z, 1);
      modify(rt[y], 1, 100000, z, 1);
      modify(rt[lca(x, y)], 1, 100000, z, -1);
      modify(rt[anc[lca(x, y)][0]], 1, 100000, z, -1);
    }
    dfs2(1, 0);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P4556::main(), 0; }
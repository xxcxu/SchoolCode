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
namespace Solution_Of_P3233 {
  bool _1;
  static const i32 N = 300005;
  i32 n, m, k;
  i32 by[N], dep[N], dfn[N], ans[N], size[N], anc[N][20];
  bool spc[N];
  std::vector<i32> spec, node;
  std::vector<i32> e[N], g[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    static i32 ts = 0;
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    dfn[x] = ++ts;
    size[x] = 1;
    for (i32 i = 1; i < 20; ++i) anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (i32 y : e[x]) if (y != fa) dfs(y, x), size[x] += size[y];
    return void();
  }
  i32 lca(i32 x, i32 y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 19; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 19; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  i32 jump(i32 x, i32 d) {
    for (i32 i = 19; i >= 0; --i)
      if (d >> i & 1) x = anc[x][i];
    return x;
  }
  i32 dis(i32 x, i32 y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
  }
  i32 st[N], top;
  void add(i32 x, i32 y) {
    if (dep[x] > dep[y]) std::swap(x, y);
    g[x].eb(y);
    return void();
  }
  void insert(i32 x) {
    if (!top) { st[++top] = x; return void(); }
    i32 l = lca(x, st[top]);
    while (top >= 2 && dep[st[top - 1]] > dep[l]) add(st[top - 1], st[top]), --top;
    if (top && dep[st[top]] > dep[l]) add(l, st[top--]);
    if (!top || l != st[top]) st[++top] = l;
    st[++top] = x;
    return void();
  }
  void erase(i32 x) {
    ans[x] = 0, spc[x] = false;
    for (i32 y : g[x]) erase(y);
    g[x].clear();
    g[x].shrink_to_fit();
    return void();
  }
  void build() {
    erase(1);
    node.clear(), spec.clear();
    top = 0;
    for (i32 i = 0; i < k; ++i) node.eb(read());
    for (i32 i : node) spc[i] = true, spec.eb(i);
    std::sort(all(node), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
    if (!spc[1]) insert(1);
    for (i32 i : node) insert(i);
    while (top >= 2) add(st[top - 1], st[top]), --top;
    st[top--] = 0;
    return void();
  }
  void dfs1(i32 x) {
    if (spc[x]) by[x] = x;
    else by[x] = -1;
    for (i32 y : g[x]) {
      dfs1(y);
      if (by[y] != -1) {
        if (by[x] == -1) by[x] = by[y];
        else {
          i32 d1 = dis(x, by[x]), d2 = dis(x, by[y]);
          if (d1 > d2 || (d1 == d2 && by[y] < by[x])) by[x] = by[y];
        }
      }
    }
    return void();
  }
  void dfs2(i32 x) {
    for (i32 y : g[x]) {
      if (by[x] != -1) {
        if (by[y] == -1) by[y] = by[x];
        else {
          i32 d1 = dis(y, by[y]), d2 = dis(y, by[x]);
          if (d1 > d2 || (d1 == d2 && by[x] < by[y])) by[y] = by[x];
        }
      }
      dfs2(y);
    }
    return void();
  }
  void dfs3(i32 x) {
    ans[by[x]] += size[x];
    for (i32 y : g[x]) {
      i32 d = dep[y] - dep[x] - 1;
      ans[by[x]] -= size[jump(y, d)];
      dfs3(y);
    }
    return void();
  }
  void dfs4(i32 x) {
    for (i32 y : g[x]) {
      i32 d = dep[y] - dep[x] - 1;
      if (by[x] != by[y]) {
        i32 d1 = dis(x, by[x]), d2 = dis(y, by[y]);
        auto check = [&](i32 mid)->bool {
          if ((d1 + mid < d2 + d + 1 - mid) || (d1 + mid == d2 + d + 1 - mid && by[x] < by[y])) return true;
          return false;
        };
        i32 l = 0, r = d, res = d + 1;
        while (l <= r) {
          i32 mid((l + r) >> 1);
          if (check(mid)) l = mid + 1, res = mid;
          else r = mid - 1;
        }
        if (res == 0) ans[by[y]] += size[jump(y, d)] - size[y];
        else if (res == d + 1) ans[by[x]] += size[jump(y, d)] - size[y];
        else {
          ans[by[x]] += size[jump(y, d)] - size[jump(y, d - res)];
          ans[by[y]] += size[jump(y, d - res)] - size[y];
        }
      } else {
        ans[by[x]] += size[jump(y, d)] - size[y];
      }
      dfs4(y);
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 0);
    m = read();
    while (m--) {
      k = read();
      build();
      dfs1(1), dfs2(1), dfs3(1), dfs4(1);
      for (i32 i : spec) fprintf(fout, "%d ", ans[i]);
      fputs("\n", fout);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P3233::main(), 0; }
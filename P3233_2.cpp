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
namespace Solution_Of_P3233 {
  bool _1;
  static const i32 N = 300005;
  i32 n, m, q;
  i32 dfn[N], tim = 0;
  i32 dep[N], size[N], by[N], ans[N], anc[N][22];
  i32 st[N], top = 0;
  bool vis[N];
  std::vector<i32> p, id, vec;
  std::vector<i32> e[N], g[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    dfn[x] = ++tim;
    anc[x][0] = fa;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    size[x] = 1;
    for (auto &y : e[x]) 
      if (y != fa) {
        dep[y] = dep[x] + 1;
        dfs(y, x);
        size[x] += size[y];
      }
    return void();
  }
  i32 lca(i32 x, i32 y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 21; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 21; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  i32 jump(i32 x, i32 d) {
    for (i32 i = 21; i >= 0; --i)
      if (d >> i & 1)
        x = anc[x][i];
    return x;
  }
  i32 dis(i32 x, i32 y) { 
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
  }
  void update(i32 x, i32 p) {
    i32 q = by[x];
    if (q == -1) by[x] = p;
    else {
      i32 d1 = dis(x, p), d2 = dis(x, q);
      if ((d1 < d2) || (d1 == d2 && p < q)) by[x] = p;
    }
    return void();
  }
  void dfs1(i32 x, i32 fa) {
    if (vis[x]) by[x] = x;
    else by[x] = -1;
    for (auto &y : g[x])
      if (y != fa) {
        dfs1(y, x);
        if (by[y] != -1) update(x, by[y]);
      }
    return void();
  }
  void dfs2(i32 x, i32 fa) {
    for (auto &y : g[x])
      if (y != fa) {
        if (by[x] != -1) update(y, by[x]);
        dfs2(y, x);
      }
    return void();
  }
  void dfs3(i32 x, i32 fa) {
    ans[by[x]] += size[x];
    for (auto &y : g[x])
      if (y != fa) {
        i32 d = dep[y] - dep[x] - 1;
        ans[by[x]] -= size[jump(y, d)];
        dfs3(y, x);
      }
    return void();
  }
  bool check(i32 x, i32 y, i32 d1, i32 d2, i32 d, i32 dis) {
    i32 dx = d1 + dis, dy = d2 + d + 1 - dis;
    if ((dx < dy) || (dx == dy && by[x] < by[y])) return true;
    return false;
  }
  void dfs4(i32 x, i32 fa) {
    for (auto &y : g[x])
      if (y != fa) {
        if (by[x] != by[y]) {
          i32 d = dep[y] - dep[x] - 1;
          i32 L = 0, R = d, res = d + 1;
          i32 d1 = dis(x, by[x]), d2 = dis(y, by[y]);
          while (L <= R) {
            i32 mid((L + R) >> 1);
            if (check(x, y, d1, d2, d, mid)) L = mid + 1, res = mid;
            else R = mid - 1;
          }
          ans[by[x]] += size[jump(y, d)] - size[jump(y, d - res)];
          ans[by[y]] += size[jump(y, d - res)] - size[y];
        } else {
          i32 d = dep[y] - dep[x] - 1;
          ans[by[x]] += size[jump(y, d)] - size[y];
        }
        dfs4(y, x);
      }
    return void();
  }
  void add(i32 x, i32 y) {
    g[x].eb(y), g[y].eb(x);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 1);
    q = read();
    while (q--) {
      m = read();
      p.clear(), id.clear(), vec.clear();
      for (i32 i = 1; i <= m; ++i) p.eb(read());
      for (auto &v : p) id.eb(v);
      std::sort(all(p), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
      for (auto &v : p) vis[v] = true, vec.eb(v);
      st[top = 1] = 1; vec.eb(1);
      for (auto &v : p)
        if (v != 1) {
          i32 L = lca(st[top], v);
          if (L != st[top]) {
            while (dfn[L] < dfn[st[top - 1]])
              add(st[top], st[top - 1]), --top;
            if (dfn[L] > dfn[st[top - 1]]) {
              vec.eb(L);
              add(L, st[top]);
              st[top] = L;
            } else {
              add(L, st[top--]);
            }
          }
          st[++top] = v;
        }
      for (i32 i = 1; i < top; ++i) add(st[i], st[i + 1]);
      dfs1(1, 1), dfs2(1, 1);
      dfs3(1, 1), dfs4(1, 1);
      for (auto &v : id) fprintf(fout, "%d ", ans[v]);
      fputs("\n", fout);
      for (auto &v : vec) g[v].clear();
      for (auto &v : p) ans[v] = 0, vis[v] = false;
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P3233 ::main(), 0; }
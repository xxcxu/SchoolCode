#pragma region
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
#pragma endregion
namespace Solution_Of_CF1416D {
  bool _1;
  static constexpr i32 N = 200005, M = 300005, Q = 500005;
  i32 n, m, q, id;
  i32 p[N * 2], ti[N * 2], redfn[N * 2], lson[N * 2], rson[N * 2], anc[N * 2][25], L[N * 2], R[N * 2];
  struct Ope {
    i32 op, v;
    Ope(i32 op = 0, i32 v = 0):
      op(op), v(v) {}
  } qu[Q];
  struct edge {
    i32 u, v, t;
    edge(i32 u = 0, i32 v = 0, i32 t = 0):
      u(u), v(v), t(t) {}
  } e[M];
  i32 fa[N * 2];
  std::vector<i32> g[N * 2];
  bool vis[M];
  bool _2;
    i32 max[N << 3], pos[N << 3];
  class SegmentTree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    public:
    void pushup(i32 x) {
      max[x] = std::max(max[ls], max[rs]);
      if (max[ls] == max[x]) pos[x] = pos[ls];
      else pos[x] = pos[rs];
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      if (l == r) {
        max[x] = p[redfn[l]];
        pos[x] = l;
        return void();
      }
      i32 mid = (l + r) >> 1;
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    std::pair<i32, i32> query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return {max[x], pos[x]};
      i32 mid = (l + r) >> 1;
      std::pair<i32, i32> ans = {0, 0};
      if (ql <= mid) ans = std::max(ans, query(ls, l, mid, ql, qr));
      if (qr > mid) ans = std::max(ans, query(rs, mid + 1, r, ql, qr));
      return ans;
    }
    void update(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) {
        max[x] = 0;
        return void();
      }
      i32 mid = (l + r) >> 1;
      if (p <= mid) update(ls, l, mid, p);
      else update(rs, mid + 1, r, p);
      return pushup(x);
    }
  } sg;
  void newNode(i32 x, i32 y, i32 t) {
    fa[x] = fa[y] = ++id;
    ti[id] = t;
    g[id].eb(x), g[id].eb(y);
    return void();
  }
  void dfs(i32 x, i32 fa) {
    static i32 dfn = 0;
    L[x] = ++dfn;
    redfn[dfn] = x;
    anc[x][0] = fa;
    for (i32 i = 1; i <= 24; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (i32 y : g[x]) dfs(y, x);
    R[x] = dfn;
    return void();
  }
  i32 query(i32 x, i32 t) {
    for (i32 i = 24; i >= 0; --i)
      if (anc[x][i] && ti[anc[x][i]] >= t)
        x = anc[x][i];
    return x;
  }
  i32 find(i32 x) { 
    return x == fa[x] ? x : fa[x] = find(fa[x]);
  }
  void exKruskal() {
    std::sort(e + 1, e + m + 1, [&](const edge &a, const edge &b)
      { return a.t > b.t; });
    id = n;
    for (i32 i = 1; i <= m; ++i) {
      auto &[u, v, t] = e[i];
      i32 fx = find(u), fy = find(v);
      if (fx == fy) continue;
      newNode(fx, fy, t);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), q = read();
    for (i32 i = 1; i <= n; ++i) p[i] = read();
    for (i32 i = 1; i <= m; ++i) e[i].u = read(), e[i].v = read();
    for (i32 i = 1; i <= q; ++i) qu[i].op = read(), qu[i].v = read();
    for (i32 i = 1; i <= m; ++i) e[i].t = q + 1;
    for (i32 i = 1; i <= q; ++i) if (qu[i].op == 2) e[qu[i].v].t = i;
    for (i32 i = 1; i <= n * 2; ++i) fa[i] = i; 
    for (i32 i = 1; i <= n * 2; ++i) ti[i] = q + 1;
    exKruskal();
    for (i32 i = 1; i <= id; ++i) if (find(i) == i) dfs(i, 0);
    sg.build(1, 1, id);
    for (i32 i = 1; i <= q; ++i)
      if (qu[i].op == 1) {
        i32 rt = query(qu[i].v, i);
        auto [p, q] = sg.query(1, 1, id, L[rt], R[rt]);
        fprintf(fout, "%d\n", p);
        sg.update(1, 1, id, q);
      }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1416D::main(), 0; }
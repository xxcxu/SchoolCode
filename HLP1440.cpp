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
namespace Solution_Of_HLP1440 {
  bool _1;
  static const i32 N = 1000005;
  i32 n;
  i32 a[N], dep[N], dfn[N], rdfn[N], size[N];
  i64 ans;
  std::vector<i32> e[N];
  bool _2;
  struct SegmenTree {
    i32 tr[N << 2], pos[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) { 
      if (tr[ls] < tr[rs]) tr[x] = tr[ls], pos[x] = pos[ls];
      else tr[x] = tr[rs], pos[x] = pos[rs];
      return void();  
    }
    void build(i32 x, i32 l, i32 r) {
      tr[x] = INT_MAX;
      if (l == r) {
        if (a[rdfn[l]] == 1)
          tr[x] = dep[rdfn[l]], pos[x] = rdfn[l];
        return void();
      }
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) {
        tr[x] = INT_MAX;
        pos[x] = 0;
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) modify(ls, l, mid, p);
      else modify(rs, mid + 1, r, p);
      return pushup(x);
    }
    std::pair<i32, i32> query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr)
        return std::make_pair(tr[x], pos[x]);
      i32 mid((l + r) >> 1);
      i32 ret = 0, now = INT_MAX;
      if (ql <= mid) {
        auto [w, p] = query(ls, l, mid, ql, qr);
        if (w < now) ret = p, now = w;
      }
      if (qr > mid) {
        auto [w, p] = query(rs, mid + 1, r, ql, qr);
        if (w < now) ret = p, now = w;
      }
      return std::make_pair(now, ret);
    }
  } seg;
  void dfs2(i32 x, i32 fa) {
    static i32 ts = 0;
    size[x] = 1;
    dfn[x] = ++ts;
    rdfn[ts] = x;
    dep[x] = dep[fa] + 1;
    for (i32 y : e[x])
      if (y != fa) {
        dfs2(y, x);
        size[x] += size[y];
      }
    return void();
  }
  void dfs(i32 x, i32 fa) {
    for (i32 y : e[x])
      if (y != fa)
        dfs(y, x);
    if (a[x] == 0) {
      i32 p = seg.query(1, 1, n, dfn[x], dfn[x] + size[x] - 1).second;
      assert(p != 0);
      ans += dep[p] - dep[x];
      seg.modify(1, 1, n, dfn[p]);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("wbtree.in", "r");
    fout = fopen("wbtree.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs2(1, 0);
    seg.build(1, 1, n);
    dfs(1, 0);
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1440::main(), 0; }
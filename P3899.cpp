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
namespace Solution_Of_ {
  bool _1;
  static const i32 N = 300005, T = 64;
  i32 n, q, tot;
  std::vector<i32> e[N];
  i32 dep[N], size[N], rt[N];
  i64 sum[N * T], ls[N * T], rs[N * T];
  bool _2;
  void pushup(i32 x) {
    sum[x] = sum[ls[x]] + sum[rs[x]];
    return void();
  }
  i32 build(i32 l, i32 r, i32 p, i32 v) {
    i32 x = ++tot;
    if (l == r) {
      sum[x] += v;
      return x;
    }
    i32 mid((l + r) >> 1);
    if (p <= mid) ls[x] = build(l, mid, p, v);
    else rs[x] = build(mid + 1, r, p, v);
    pushup(x);
    return x;
  }
  i32 merge(i32 x, i32 y, i32 l, i32 r) {
    if (!x || !y) return x + y;
    if (l == r) {
      i32 p = ++tot;
      sum[p] = sum[x] + sum[y];
      return p;
    }
    i32 mid((l + r) >> 1), p = ++tot;
    ls[p] = merge(ls[x], ls[y], l, mid);
    rs[p] = merge(rs[x], rs[y], mid + 1, r);
    pushup(p);
    return p;
  }
  i64 query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
    if (!x) return 0;
    if (ql <= l && r <= qr) return sum[x];
    i32 mid((l + r) >> 1);
    i64 ans = 0;
    if (ql <= mid) ans += query(ls[x], l, mid, ql, qr);
    if (qr > mid) ans += query(rs[x], mid + 1, r, ql, qr);
    return ans;
  }
  void dfs(i32 x, i32 fa) {
    dep[x] = dep[fa] + 1;
    size[x] = 1;
    for (auto &y : e[x]) 
      if (y != fa) {
        dfs(y, x);
        size[x] += size[y];
      }
    return void();
  }
  void dfs2(i32 x, i32 fa) {
    rt[x] = build(1, n, dep[x], size[x] - 1);
    for (auto &y : e[x])
      if (y != fa) {
        dfs2(y, x);
        rt[x] = merge(rt[x], rt[y], 1, n);
      }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), q = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 1);
    dfs2(1, 1);
    i64 ans = 0;
    while (q--) {
      static i32 p, k;
      p = read(), k = read();
      ans += 1ll * std::min(dep[p] - 1, k) * (size[p] - 1);
      if (dep[p] != n) ans += query(rt[p], 1, n, dep[p] + 1, std::min(dep[p] + k, n));
      fprintf(fout, "%lld\n", ans);
      ans = 0;
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }
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
namespace Solution_Of_P5298 {
  bool _1;
  static const i32 N = 300005, T = 60, P = 998244353;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
      i32 ans = 1;
      for (; y; y >>= 1, x = mul(x, x))
          if (y & 1) ans = mul(ans, x);
      return ans;
  }
  i32 inv(i32 x) { return qpow(x, P - 2); }
  i32 n, cnt, tot, ans;
  i32 val[N], a[N], rt[N], p[N];
  i32 multi[N * T], sum[N * T], ls[N * T], rs[N * T];
  std::vector<i32> son[N];
  bool _2;
  bool leaf(i32 x) { return son[x].empty(); }
  void pushup(i32 x) {
    sum[x] = inc(sum[ls[x]], sum[rs[x]]);
    return void();
  }
  void pushmul(i32 x, i32 v) {
    if (!x) return void();
    sum[x] = mul(sum[x], v);
    multi[x] = mul(multi[x], v);
    return void();
  }
  void pushdown(i32 x) {
    if (multi[x] == 1) return void();
    pushmul(ls[x], multi[x]);
    pushmul(rs[x], multi[x]);
    multi[x] = 1;
  } 
  i32 build(i32 l, i32 r, i32 p) {
    i32 x = ++tot;
    multi[x] = 1, sum[x] = 0;
    if (l == r)
      return sum[x] = 1, x;
    i32 mid((l + r) >> 1);
    if (p <= mid) ls[x] = build(l, mid, p);
    else rs[x] = build(mid + 1, r, p);
    return pushup(x), x;
  }
  i32 merge(i32 x, i32 y, i32 l, i32 r, i32 xmul, i32 ymul, i32 p) {
    if (!x || !y) {
      pushmul(x | y, x ? xmul : ymul);
      return x | y;
    }
    pushdown(x), pushdown(y);
    i32 mid((l + r) >> 1);
    i32 v1 = inc(xmul, mul(sum[rs[y]], dec(1, p)));
    i32 v2 = inc(xmul, mul(sum[ls[y]], p));
    i32 v3 = inc(ymul, mul(sum[rs[x]], dec(1, p)));
    i32 v4 = inc(ymul, mul(sum[ls[x]], p));
    ls[x] = merge(ls[x], ls[y], l, mid, v1, v3, p);
    rs[x] = merge(rs[x], rs[y], mid + 1, r, v2, v4, p);
    return pushup(x), x;
  }
  void dfs(i32 x) {
    for (auto y : son[x]) dfs(y);
    if (leaf(x)) rt[x] = build(1, cnt, val[x]);
    else if ((i32)son[x].size() == 1) rt[x] = rt[son[x][0]];
    else rt[x] = merge(rt[son[x][0]], rt[son[x][1]], 1, cnt, 0, 0, val[x]);
    return void();
  }
  void dfs2(i32 x, i32 l, i32 r) {
    if (l == r)
      return p[l] = mul(sum[x], sum[x]), void();
    i32 mid((l + r) >> 1);
    pushdown(x);
    dfs2(ls[x], l, mid), dfs2(rs[x], mid + 1, r);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      i32 fa = read();
      son[fa].eb(i);
    }
    for (i32 i = 1; i <= n; ++i) {
      val[i] = read();
      if (!leaf(i)) val[i] = mul(val[i], inv(10000));
      else a[++cnt] = val[i];
    }
    std::sort(a + 1, a + cnt + 1);
    for (i32 i = 1; i <= n; ++i)
      if (leaf(i)) val[i] = std::lower_bound(a + 1, a + cnt + 1, val[i]) - a;
    dfs(1);
    dfs2(rt[1], 1, cnt);
    for (i32 i = 1; i <= cnt; ++i)
      ans = inc(ans, mul(i, mul(a[i], p[i])));
    fprintf(fout, "%d\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P5298::main(), 0; }
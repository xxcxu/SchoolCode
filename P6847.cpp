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
namespace Solution_Of_P6847 {
  bool _1;
  static const i32 N = 100005, T = 420;
  i32 n, m, k, cnt;
  i32 v[N], d[N], w[N], rt[N];
  std::vector<i32> e[N];
  i32 ls[N * T], rs[N * T];
  i64 d1, d2;
  i64 max[N * T], tag[N * T];
  bool _2;
  void pushup(i32 x) {
    max[x] = std::max(max[ls[x]], max[rs[x]]);
    return void();
  }
  void pushtag(i32 &x, i64 v) {
    if (!x) x = ++cnt;
    max[x] += v;
    tag[x] += v;
    return void();
  }
  void pushdown(i32 x) {
    if (!tag[x]) return void();
    if (ls[x]) pushtag(ls[x], tag[x]);
    if (rs[x]) pushtag(rs[x], tag[x]);
    tag[x] = 0;
    return void();
  }
  i32 modify(i32 x, i32 l, i32 r, i32 p, i64 v) {
    if (!x) x = ++cnt;
    if (l == r) {
      max[x] = std::max(max[x], v);
      return x;
    }
    pushdown(x);
    i32 mid((l + r) >> 1);
    if (p <= mid) ls[x] = modify(ls[x], l, mid, p, v);
    else rs[x] = modify(rs[x], mid + 1, r, p, v);
    pushup(x);
    return x;
  }
  i32 merge(i32 x, i32 y, i32 l, i32 r) {
    if (!x && !y) return 0;
    if (!x) {
      d2 = std::max(d2, max[y]);
      pushtag(y, d1);
      return y;
    }
    if (!y) {
      d1 = std::max(d1, max[x]);
      pushtag(x, d2);
      return x;
    }
    if (l == r) {
      d1 = std::max(d1, max[x]);
      d2 = std::max(d2, max[y]);
      max[x] = std::max(max[x] + d2, max[y] + d1);
      return x;
    }
    pushdown(x), pushdown(y);
    i32 mid((l + r) >> 1);
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid + 1, r);
    pushup(x);
    return x;
  }
  i64 query(i32 x, i32 l, i32 r, i32 p) {
    if (!x) return 0;
    if (r <= p) return max[x];
    pushdown(x);
    i32 mid((l + r) >> 1);
    if (p <= mid) return query(ls[x], l, mid, p);
    else return std::max(query(ls[x], l, mid, p), query(rs[x], mid + 1, r, p));
  }
  void dfs(i32 x) {
    for (auto &y : e[x]) {
      dfs(y); 
      d1 = d2 = 0;
      rt[x] = merge(rt[x], rt[y], 1, k);
    }
    if (d[x]) rt[x] = modify(rt[x], 1, k, d[x], w[x] + query(rt[x], 1, k, d[x]));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read(), k = read();
    for (i32 i = 2; i <= n; ++i) {
      static i32 fa;
      fa = read();
      e[fa].eb(i);
    }
    for (i32 i = 1; i <= m; ++i) v[i] = read(), d[v[i]] = read(), w[v[i]] = read();
    dfs(1);
    fprintf(fout, "%lld\n", max[rt[1]]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P6847::main(), 0; }
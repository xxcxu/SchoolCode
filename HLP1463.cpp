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
namespace Solution_Of_HLP1463 {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 998244353;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void plus(i32 &x, i32 y) { return x = inc(x, y), void(); }
  void cmul(i32 &x, i32 y) { return x = mul(x, y), void(); }
  i32 n, k, ans;
  i32 c[N], size[N], son[N], rt[N];
  std::vector<i32> e[N];
  bool _2;
  struct SegmentTree {
    static const i32 M = N << 4;
    i32 ls[M], rs[M], len[M], tot;
    struct treeNode {
      i32 val, sum, lazy_add, lazy_mul;
      treeNode() = default;
      treeNode(i32 _val, i32 _sum, i32 _lazy_add, i32 _lazy_mul):
        val(_val), sum(_sum), lazy_add(_lazy_add), lazy_mul(_lazy_mul) {}
    } tr[M];
    i32 newNode() {
      ++tot;
      tr[tot] = treeNode(0, 0, 0, 1);
      return tot;
    }
    void pushup(i32 x) { return tr[x].sum = inc(tr[ls[x]].sum, tr[rs[x]].sum), void(); }
    void pushtag_add(i32 x, i32 v) {
      plus(tr[x].val, v);
      plus(tr[x].sum, mul(len[x], v));
      if (x) plus(tr[x].lazy_add, v);
      return void();
    }
    void pushtag_mul(i32 x, i32 v) {
      cmul(tr[x].val, v);
      cmul(tr[x].sum, v);
      if (x) cmul(tr[x].lazy_add, v);
      if (x) cmul(tr[x].lazy_mul, v);
      return void();
    }
    void pushdown(i32 x) {
      if (tr[x].lazy_mul != 1) {
        pushtag_mul(ls[x], tr[x].lazy_mul);
        pushtag_mul(rs[x], tr[x].lazy_mul);
        tr[x].lazy_mul = 1;
      }
      if (tr[x].lazy_add != 0) {
        pushtag_add(ls[x], tr[x].lazy_add);
        pushtag_add(rs[x], tr[x].lazy_add);
        tr[x].lazy_add = 0;
      }
      return void();
    }
    void modify(i32 &x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (!x) x = newNode(), len[x] = r - l + 1;
      if (ql <= l && r <= qr)
        return pushtag_add(x, v);
      i32 mid((l + r) >> 1);
      if (ql <= mid) modify(ls[x], l, mid, ql, qr, v);
      if (qr > mid) modify(rs[x], mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    void merge(i32 &x, i32 &y, i32 l, i32 r, i32 s) {
      if (!x) return void();
      if (!y) {
        pushtag_mul(x, s);
        return void();
      }
      if (!ls[y] && !rs[y]) {
        pushtag_mul(x, dec(s, tr[y].val));
        return void();
      }
      if (!ls[x] && !rs[x]) {
        std::swap(x, y);
        pushtag_mul(x, P - 1);
        pushtag_add(x, s);
        pushtag_mul(x, tr[y].val);
        return void();
      }
      if (l == r) {
        pushtag_mul(x, dec(s, tr[y].val));
        return void();
      }
      i32 mid((l + r) >> 1);
      if (!ls[x]) ls[x] = newNode(), len[ls[x]] = mid - l + 1;
      if (!ls[y]) ls[y] = newNode(), len[ls[y]] = mid - l + 1;
      if (!rs[x]) rs[x] = newNode(), len[rs[x]] = r - mid;
      if (!rs[y]) rs[y] = newNode(), len[rs[y]] = r - mid;  
      pushdown(x);
      pushdown(y);
      merge(ls[x], ls[y], l, mid, s);
      merge(rs[x], rs[y], mid + 1, r, s);
      return pushup(x);
    }
  } seg;
  void dfs1(i32 x, i32 fa) {
    if (fa) e[x].erase(find(all(e[x]), fa));
    size[x] = 1;
    for (i32 y : e[x]) {
      dfs1(y, x);
      size[x] += size[y];
      if (size[y] > size[son[x]]) son[x] = y;
    }
    return void();
  }
  void dfs2(i32 x) {
    if (!c[x]) seg.modify(rt[x], 1, k, 1, k, 1);
    else seg.modify(rt[x], 1, k, c[x], c[x], 1);
    if (son[x]) e[x].erase(find(all(e[x]), son[x]));
    if (son[x]) dfs2(son[x]), seg.merge(rt[x], rt[son[x]], 1, k, seg.tr[rt[son[x]]].sum);
    for (i32 y : e[x]) dfs2(y), seg.merge(rt[x], rt[y], 1, k, seg.tr[rt[y]].sum);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("color.in", "r");
    fout = fopen("color.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read();
    for (i32 i = 1; i <= n; ++i) c[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    i64 Start_Time_Without_Read = clock();
    dfs1(1, 0);
    dfs2(1);
    fprintf(fout, "%d\n", seg.tr[rt[1]].sum);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1463::main(), 0; }
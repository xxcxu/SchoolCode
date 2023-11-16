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
namespace Solution_Of_HLP1546 {
  bool _1;
  static const i32 N = 500005;
  i32 n, m, q, k, d, rt;
  i32 a[N], x[N], y[N];
  struct SegmentTree {
    struct TreeNode {
      i64 lmx, rmx, mx, sum;
      TreeNode() = default;
      TreeNode(i64 v): lmx(v), rmx(v), mx(v), sum(v) {}
      TreeNode(i64 _lmx, i64 _rmx, i64 _mx, i64 _sum):
        lmx(_lmx), rmx(_rmx), mx(_mx), sum(_sum) {}
      TreeNode operator +(const TreeNode other) const {
        TreeNode ret;
        ret.lmx = std::max(this->lmx, this->sum + other.lmx);
        ret.rmx = std::max(other.rmx, this->rmx + other.sum);
        ret.mx = std::max({this->mx, other.mx, this->rmx + other.lmx}); 
        ret.sum = this->sum + other.sum;
        return ret;
      }
    } tr[N << 4];
    i32 tot = 1;
    i32 ls[N << 4], rs[N << 4];
    i32 newNode() { return ++tot; }
    void pushup(i32 x, i32 l, i32 r) {
      i32 mid((l + r) >> 1);
      TreeNode lst = ls[x] ? tr[ls[x]] : TreeNode(-k, -k, -k, -1LL * k * (mid - l + 1));
      TreeNode rst = rs[x] ? tr[rs[x]] : TreeNode(-k, -k, -k, -1LL * k * (r - mid));
      tr[x] = lst + rst;
      return void();
    }
    void modify(i32 &x, i32 l, i32 r, i32 p, i32 v) {
      if (!x) x = newNode();
      if (l == r) {
        tr[x] = TreeNode(tr[x].sum + v);
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) modify(ls[x], l, mid, p, v);
      else modify(rs[x], mid + 1, r, p, v);
      return pushup(x, l, r);
    }
  } seg1;
  struct SegmentTree2 {
    i64 tr[N << 2];
    i64 tag[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) {
      return tr[x] = std::max(tr[ls], tr[rs]), void();
    }
    void pushdown(i32 x) {
      if (tag[x]) {
        tr[ls] += tag[x], tag[ls] += tag[x];
        tr[rs] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
      }
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      if (l == r) {
        tr[x] = 1LL * a[l] * k;
        return void();
      }
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        tr[x] += v;
        tag[x] += v;
        return void();
      }
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (ql <= mid) modify(ls, l, mid, ql, qr, v);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    #undef ls
    #undef rs
  } seg2;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("glass.in", "r");
    fout = fopen("glass.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), q = read(), k = read(), d = read();
    for (i32 i = 1; i <= q; ++i) x[i] = read(), y[i] = read();
    for (i32 i = 1; i <= q; ++i) a[++m] = x[i];
    std::sort(a + 1, a + m + 1);
    m = std::unique(a + 1, a + m + 1) - a - 1;
    rt = 1;
    seg2.build(rt, 1, m);
    for (i32 i = 1; i <= m; ++i) seg1.modify(rt, 1, n, a[i], -k);
    for (i32 i = 1; i <= q; ++i) {
      i32 p = std::lower_bound(a + 1, a + m + 1, x[i]) - a;
      if (x[i] + d <= n) seg1.modify(rt, 1, n, x[i], y[i]);
      seg2.modify(rt, 1, m, 1, p, y[i]);
      i64 t1 = seg1.tr[rt].mx;
      i64 t2 = seg2.tr[rt];
      fputs(t1 <= 1LL * d * k && t2 <= 1LL * k * (n + 1) ? "Yes\n" : "No\n", fout);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read); 
    return void();
  }
}
signed main() { return Solution_Of_HLP1546::main(), 0; }
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
  static const i64 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 n, q, k, d, rt;
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
    } tr[N * 4];
    i32 ls(i32 x) { return x << 1; }
    i32 rs(i32 x) { return x << 1 | 1; }
    void pushup(i32 x) {
      tr[x] = tr[ls(x)] + tr[rs(x)];
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      if (l == r) {
        tr[x] = TreeNode(-k);
        return void();
      }
      i32 mid((l + r) >> 1);
      build(ls(x), l, mid);
      build(rs(x), mid + 1, r);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 p, i32 v) {
      if (l == r) {
        tr[x] = TreeNode(tr[x].sum + v);
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) modify(ls(x), l, mid, p, v);
      else modify(rs(x), mid + 1, r, p, v);
      return pushup(x);
    }
  } seg;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("glass.in", "r");
    // fout = fopen("glass.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), q = read(), k = read(), d = read();
    rt = 1;
    seg.build(1, 1, n);
    for (i32 i = 1; i <= q; ++i) {
      static i32 x, y;
      x = read(), y = read();
      seg.modify(rt, 1, n, x, y); 
      i64 t = seg.tr[rt].mx;
      fputs(t <= 1LL * d * k ? "TAK\n" : "NIE\n", fout);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1546::main(), 0; }
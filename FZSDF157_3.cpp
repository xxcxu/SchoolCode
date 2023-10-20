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
namespace Solution_Of_FZSDF157_3 {
  bool _1;
  static const i32 N = 200005;
  static const i32 P = 998244353;
  i32 n, m;
  struct Node {
    i32 l, r, c;
    Node() = default;
    Node(i32 l, i32 r, i32 c): l(l), r(r), c(c) {}
  } a[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  struct SegmentTree {
    std::pair<i64, i32> fg[N << 2];
    i64 tag[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(std::pair<i64, i32> &x, std::pair<i64, i32> lson, std::pair<i64, i32> rson) {
      x.first = std::max(lson.first, rson.first);
      x.second = 0;
      if (x.first == lson.first) x.second = inc(x.second, lson.second);
      if (x.first == rson.first) x.second = inc(x.second, rson.second);
      return void();
    }
    void pushtag(i32 x, i64 v) {
      fg[x].first += v;
      tag[x] += v;
      return void();
    }
    void pushdown(i32 x) {
      if (tag[x]) {
        pushtag(ls, tag[x]);
        pushtag(rs, tag[x]);
        tag[x] = 0;
      }
      return void();
    }
    void change(i32 x, i32 l, i32 r, i32 p, i64 _f, i32 _g) {
      if (l == r) return fg[x].first = _f, fg[x].second = _g, void();
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (p <= mid) change(ls, l, mid, p, _f, _g);
      else change(rs, mid + 1, r, p, _f, _g);
      return pushup(fg[x], fg[ls], fg[rs]);
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 _f) {
      if (ql <= l && r <= qr)
        return pushtag(x, _f), void();
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (ql <= mid) modify(ls, l, mid, ql, qr, _f);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, _f);
      return pushup(fg[x], fg[ls], fg[rs]);
    }
    std::pair<i64, i32> query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return fg[x];
      i32 mid((l + r) >> 1);
      std::pair<i64, i32> ans(0, 0);
      pushdown(x);
      if (ql <= mid) pushup(ans, ans, query(ls, l, mid, ql, qr));
      if (qr > mid) pushup(ans, ans, query(rs, mid + 1, r, ql, qr));
      return ans;
    }
  } seg;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    #ifdef ONLINE_JUDGE
    fin = fopen("standard.in", "r");
    fout = fopen("standard.out", "w");
    #endif
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i)
      a[i].l = read(), a[i].r = read(), a[i].c = read();
    i64 Start_Time_Without_Read = clock();
    seg.change(1, 1, m, 1, 0, 1);
    for (i32 i = 1; i <= n; ++i) {
      std::pair<i64, i32> fg = seg.query(1, 1, m, 1, a[i].l);
      i64 f = fg.first; i32 g = fg.second;
      f += a[i].c;
      seg.change(1, 1, m, a[i].l, f, g);
      if (a[i].l < a[i].r) seg.modify(1, 1, m, a[i].l + 1, a[i].r, a[i].c);
    }
    fprintf(fout, "%lld %d\n", seg.fg[1].first, seg.fg[1].second);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF157_3::main(), 0; }
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
namespace Solution_Of_CF1888D1 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m;
  i32 a[N], b[N], c[N * 2];
  bool _2;
  struct SegmentTree {
    i32 tr[N << 3], tag[N << 3];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) { return tr[x] = std::max(tr[ls], tr[rs]), void(); }
    void pushdown(i32 x) {
      if (tag[x]) {
        tr[ls] += tag[x]; tag[ls] += tag[x];
        tr[rs] += tag[x]; tag[rs] += tag[x];
        tag[x] = 0;
      }
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      tr[x] = 0, tag[x] = 0;
      if (l == r) return void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return void();
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql > qr) return void();
      if (ql <= l && r <= qr) {
        tr[x] += v;
        tag[x] += v;
        return void();
      }
      pushdown(x);
      i32 mid = ((l + r) >> 1);
      if (ql <= mid) modify(ls, l, mid, ql, qr, v);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    i32 query(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x];
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (p <= mid) return query(ls, l, mid, p);
      else return query(rs, mid + 1, r, p);
    }
  } seg;
  void solve() {
    n = read(), m = read();
    i32 l = 0;
    c[++l] = 1;
    for (i32 i = 2; i <= n; ++i) a[i] = read(), c[++l] = a[i];
    for (i32 i = 1; i <= n; ++i) b[i] = read(), c[++l] = b[i];
    std::sort(c + 1, c + l + 1);
    l = std::unique(c + 1, c + l + 1) - c - 1;
    for (i32 i = 1; i <= n; ++i) a[i] = std::lower_bound(c + 1, c + l + 1, a[i]) - c;
    for (i32 i = 1; i <= n; ++i) b[i] = std::lower_bound(c + 1, c + l + 1, b[i]) - c;
    seg.build(1, 1, l);
    for (i32 i = 2; i <= n; ++i) seg.modify(1, 1, l, 1, a[i], 1);
    for (i32 i = 1; i <= n; ++i) seg.modify(1, 1, l, 1, b[i] - 1, -1);
    for (i32 i = 1; i <= m; ++i) {
      if (i > 1) seg.modify(1, 1, l, 1, i - 1, -1);
      seg.modify(1, 1, l, 1, i, 1);
      fprintf(fout, "%d\n", seg.tr[1]);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1888D1::main(), 0; }
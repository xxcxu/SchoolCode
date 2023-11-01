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
namespace Solution_Of_HLP1487 {
  bool _1;
  static const i32 N = 500005;
  i32 n, m;
  i32 a[N], b[N];
  i32 tot = 0;
  i32 tr[N << 6], ls[N << 6], rs[N << 6];
  i32 rt[N][2], ans[N];
  bool _2;
  i32 newNode() { return ++tot; }
  struct SegmentTree {
    void pushup(i32 x) { return tr[x] = tr[ls[x]] + tr[rs[x]], void(); }
    void insert(i32 &x, i32 y, i32 l, i32 r, i32 p) {
      x = newNode();
      tr[x] = tr[y];
      ls[x] = ls[y], rs[x] = rs[y];
      if (l == r) {
        ++tr[x];
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) insert(ls[x], ls[y], l, mid, p);
      else insert(rs[x], rs[y], mid + 1, r, p);
      return pushup(x);
    }
    i32 count(i32 x, i32 y, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql > qr) return 0;
      if (ql <= l && r <= qr)
        return tr[y] - tr[x];
      i32 mid((l + r) >> 1), ans = 0;
      if (ql <= mid) ans += count(ls[x], ls[y], l, mid, ql, qr);
      if (qr > mid) ans += count(rs[x], rs[y], mid + 1, r, ql, qr);
      return ans;
    }
  } seg[2];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("string.in", "r");
    fout = fopen("string.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= m; ++i) b[i] = read();
    i64 Start_Time_Without_Read = clock();
    rt[0][0] = newNode(), rt[0][1] = newNode();
    for (i32 i = 1; i <= n; ++i) seg[0].insert(rt[i][0], rt[i - 1][0], 1, n, a[i]);
    for (i32 i = 1; i <= m; ++i) seg[1].insert(rt[i][1], rt[i - 1][1], 1, m, b[i]);
    for (i32 i = m; i >= 1; --i) {
      ans[i] = std::min(m - i + 1, n);
      for (i32 j = 1; j <= std::min(n, m - i + 1); ++j) {
        i32 ret0 = 0, ret1 = 0;
        ret0 = seg[0].count(rt[0][0], rt[j][0], 1, n, 1, a[j] - 1);
        ret1 = seg[1].count(rt[i - 1][1], rt[i + j - 1][1], 1, m, 1, b[i + j - 1] - 1);
        i32 res0 = 0, res1 = 0;
        res0 = seg[0].count(rt[0][0], rt[j][0], 1, n, a[j], a[j]);
        res1 = seg[1].count(rt[i - 1][1], rt[i + j - 1][1], 1, m, b[i + j - 1], b[i + j - 1]);
        if (ret0 != ret1 || res0 != res1) {
          ans[i] = j - 1;
          break;
        }
      }
    }
    for (i32 i = 1; i <= m; ++i) fprintf(fout, "%d%c", ans[i], " \n"[i == m]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1487::main(), 0; }
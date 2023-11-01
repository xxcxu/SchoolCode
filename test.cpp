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
  i32 a[N * 2];
  bool _2;
  i32 tot = 0;
  i32 tr[N << 5], ls[N << 5], rs[N << 5];
  i32 rt[N * 2];
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
  } seg;
  i32 z[N * 2];
  bool compare(i32 p, i32 len) {
    i32 ret0 = 0, ret1 = 0;
    i32 res0 = 0, res1 = 0;
    ret0 = seg.count(rt[0], rt[len], 1, std::max(n, m), 1, a[len] - 1);
    res0 = seg.count(rt[0], rt[len], 1, std::max(n, m), a[len], a[len]);
    ret1 = seg.count(rt[p - 1], rt[p + len - 1], 1, std::max(n, m), 1, a[p + len - 1] - 1);
    res1 = seg.count(rt[p - 1], rt[p + len - 1], 1, std::max(n, m), a[p + len - 1], a[p + len - 1]);
    return ret0 == ret1 && res0 == res1;
  }
  void init() {
    for (i32 i = 2, p = 1; i <= n + m; ++i) {
      z[i] = 0;
      if (p + z[p] - i >= 0) z[i] = std::min(z[i - p + 1], p + z[p] - i);
      while (i + z[i] <= n + m && compare(i, z[i] + 1)) ++z[i];
      if (i + z[i] > p + z[p]) p = i;
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("string.in", "r");
    fout = fopen("string.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= m; ++i) a[i + n] = read();
    i64 Start_Time_Without_Read = clock();
    rt[0] = newNode();
    for (i32 i = 1; i <= n + m; ++i) seg.insert(rt[i], rt[i - 1], 1, std::max(n, m), a[i]);
    init();
    for (i32 i = n + 1; i <= n + m; ++i) fprintf(fout, "%d%c", std::min(z[i], n), " \n"[i == n + m]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1487::main(), 0; }
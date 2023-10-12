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
namespace Solution_Of_HLP1373 {
  bool _1;
  static const i32 N = 1000005;
  static const i32 inf32 = N + 1;
  i32 n, m, res;
  i32 a[N], b[N], c[N], ans[N];
  struct SegmentTree {
    i32 tr[N << 2], tag[N << 2];
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
    i32 query1(i32 x, i32 l, i32 r, i32 lmx, i32 rmx, i32 p) {
      if (l == r) return l;
      pushdown(x);
      i32 mid((l + r) >> 1);
      i32 mx1 = std::max(tr[ls], lmx), mx2 = std::max(tr[rs], rmx);
      if (p > mid) return query1(rs, mid + 1, r, mx1, rmx, p);
      if (std::max(mx1 + 1, mx2) == res) return query1(rs, mid + 1, r, mx1, rmx, p);
      else return query1(ls, l, mid, lmx, mx2, p);
    }
    i32 query2(i32 x, i32 l, i32 r, i32 lmx, i32 rmx, i32 p) {
      if (l == r) return l;
      pushdown(x);
      i32 mid((l + r) >> 1);
      i32 mx1 = std::max(tr[ls], lmx), mx2 = std::max(tr[rs], rmx);
      if (p <= mid) return query2(ls, l, mid, lmx, mx2, p);
      if (std::max(mx1 + 1, mx2) == res) return query2(rs, mid + 1, r, mx1, rmx, p);
      else return query2(ls, l, mid, lmx, mx2, p);
    }
  } seg;
  std::multiset<i32> s;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), c[++m] = a[i];
    for (i32 i = 1; i <= n; ++i) b[i] = read(), c[++m] = b[i];
    i64 Start_Time_Without_Read = clock();
    std::sort(c + 1, c + m + 1);
    m = std::unique(c + 1, c + m + 1) - c - 1;
    for (i32 i = 1; i <= n; ++i) a[i] = std::lower_bound(c + 1, c + m + 1, a[i]) - c;
    for (i32 i = 1; i <= n; ++i) b[i] = std::lower_bound(c + 1, c + m + 1, b[i]) - c;
    for (i32 i = 1; i <= n; ++i) seg.modify(1, 1, m, 1, a[i], 1);
    for (i32 i = 1; i <= n; ++i) seg.modify(1, 1, m, 1, b[i] - 1, -1); 
    for (i32 i = 1; i <= n; ++i) s.ep(b[i]);
    res = seg.tr[1];
    for (i32 i = 1; i <= n; ++i) {
      seg.modify(1, 1, m, 1, a[i], -1);
      i32 w = -1;
      if (s.upper_bound(a[i]) != s.end()) {
        w = seg.query1(1, 1, m, -inf32, -inf32, a[i] + 1);
      } else {
        --res;
        w = seg.query2(1, 1, m, -inf32, -inf32, a[i]);
      }
      auto it = --s.upper_bound(w);
      seg.modify(1, 1, m, 1, *it - 1, 1);
      ans[i] = *it;
      s.erase(it);
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d%c", c[ans[i]], " \n"[i == n]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1373::main(), 0; }
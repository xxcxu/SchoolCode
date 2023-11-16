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
namespace Solution_Of_HLP1493 {
  bool _1;
  static const i32 N = 100005;
  i32 id, n, m;
  i32 a[N];
  std::map<i32, i64> map;
  bool _2;
  i64 gcd(i64 x, i64 y) {
    return !y ? x : gcd(y, x % y);
  }
  i64 lcm(i64 x, i64 y) {
    if (x == 1000000001 || y == 1000000001) return 1000000001;
    return x / gcd(x, y) * y;
  }
  struct SegmentTree {
    i64 tr[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) {
      tr[x] = lcm(tr[ls], tr[rs]);
      if (tr[x] > 1000000000) tr[x] = 1000000001; 
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      if (l == r)
        return tr[x] = a[l], void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    void change(i32 x, i32 l, i32 r, i32 p, i32 v) {
      if (l == r)
        return tr[x] = v, void();
      i32 mid((l + r) >> 1);
      if (p <= mid) change(ls, l, mid, p, v);
      else change(rs, mid + 1, r, p, v);
      return pushup(x);
    }
    i32 find(i32 x, i32 l, i32 r, i32 pos, i32 v) {
      if (l == r) return l;
      i32 mid((l + r) >> 1);
      if (pos > mid) return find(rs, mid + 1, r, pos, v);
      if (lcm(lcm(tr[ls], v), a[mid + 1]) == v) return find(rs, mid + 1, r, pos, v);
      else return find(ls, l, mid, pos, v);
    }
    i64 query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return tr[x];
      i32 mid((l + r) >> 1);
      if (ql > mid) return query(rs, mid + 1, r, ql, qr);
      if (qr <= mid) return query(ls, l, mid, ql, qr);
      return lcm(query(ls, l, mid, ql, qr), query(rs, mid + 1, r, ql, qr));
    }
  } seg;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("cu.in", "r");
    fout = fopen("cu.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    id = read(), n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    seg.build(1, 1, n);
    if (id > 8) {
      for (i32 i = 1; i <= n; ++i) {
        i32 v = a[i], l = i, r = seg.find(1, 1, n, i, v);
        i32 lst = r;
        while (lst + 1 <= n && v <= 1000000000) {
          map[v] += (r - l + 1);
          l = lst + 1;
          v = seg.query(1, 1, n, i, l);
          r = seg.find(1, 1, n, l, v);
          lst = r;
        }
      }
      for (i32 i = 1; i <= m; ++i) {
        static i32 op, x;
        op = read(), x = read();
        if (op == 2) fprintf(fout, "%lld\n", map[x]);
      }
    } else {
      while (m--) {
        static i32 op, x, v;
        op = read(), x = read();
        if (op == 1) {
          v = read();
          a[x] = v;
          seg.change(1, 1, n, x, v);
        } else {
          i64 ans = 0;
          for (i32 i = 1, j = 1, k = 1; i <= n; ++i) {
            j = std::max(i, j);
            k = std::max(i, k);
            while (j <= n && seg.query(1, 1, n, i, j) < x) ++j;
            // =lcm
            while (k <= n && seg.query(1, 1, n, i, k) <= x) ++k;
            // >lcm
            if (j <= n && seg.query(1, 1, n, i, j) == x) ans += k - j;
          }
          fprintf(fout, "%lld\n", ans);
        }
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1493::main(), 0; }
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
namespace Solution_Of_P5445 {
  bool _1;
  static const i32 N = 300005;
  i32 n, m, q;
  char s[N], a[N];
  bool _2;
  namespace SegmentTree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    struct Seg1 {
      i32 L[N << 2], R[N << 2], tag[N << 2][2];
      void pushdown(i32 x) {
        if (tag[x][0]) {
          L[ls] = tag[x][0];
          L[rs] = tag[x][0];
          tag[ls][0] = tag[x][0];
          tag[rs][0] = tag[x][0];
          tag[x][0] = 0;
        }
        if (tag[x][1]) {
          R[ls] = tag[x][1];
          R[rs] = tag[x][1];
          tag[ls][1] = tag[x][1];
          tag[rs][1] = tag[x][1];
          tag[x][1] = 0;
        }
        return void();
      }
      void change(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v, i32 o) {
        if (ql <= l && r <= qr) {
          if (o == 0) L[x] = v;
          if (o == 1) R[x] = v;
          tag[x][o] = v;
          return void();
        }
        pushdown(x);
        i32 mid((l + r) >> 1);
        if (ql <= mid) change(ls, l, mid, ql, qr, v, o);
        if (qr > mid) change(rs, mid + 1, r, ql, qr, v, o);
        return void();        
      }
      i32 query(i32 x, i32 l, i32 r, i32 p, i32 o) {
        if (l == r) return o ? R[x] : L[x];
        pushdown(x);
        i32 mid((l + r) >> 1);
        if (p <= mid) return query(ls, l, mid, p, o);
        else return query(rs, mid + 1, r, p, o);
      }
    } seg1;
    struct Seg2 {
      i32 tot;
      i32 tag[N * 100], lson[N * 100], rson[N * 100];
      void pushdown(i32 x) {
        if (tag[x]) {
          if (!lson[x]) lson[x] = ++tot;
          tag[lson[x]] += tag[x];
          if (!rson[x]) rson[x] = ++tot;
          tag[rson[x]] += tag[x];
          tag[x] = 0;
        }
        return void();
      }
      void change(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
        if (ql <= l && r <= qr) {
          tag[x] += v;
          return void();
        }
        pushdown(x);
        i32 mid((l + r) >> 1);
        if (ql <= mid) {
          if (!lson[x]) lson[x] = ++tot;
          change(lson[x], l, mid, ql, qr, v);
        }
        if (qr > mid) {
          if (!rson[x]) rson[x] = ++tot;
          change(rson[x], mid + 1, r, ql, qr, v);
        }
        return void();
      }
      i32 query(i32 x, i32 l, i32 r, i32 p) {
        if (!x) return 0;
        if (l == r) return tag[x];
        pushdown(x);
        i32 mid((l + r) >> 1);
        if (p <= mid) return query(lson[x], l, mid, p);
        else return query(rson[x], mid + 1, r, p);
      }
    } seg2;
    struct Seg3 {
      void add(i32 x, i32 y1, i32 y2, i32 v) {
        if (!x) return void();
        for (; x <= n; x += x & -x) {
          seg2.change(x, 1, n, y1, y2, v);
        }
        return void();
      }
      void change(i32 x1, i32 y1, i32 x2, i32 y2, i32 v) {
        add(x1, y1, y2, v);
				add(x2 + 1, y1, y2, -v);
        return void();
      }
      i32 ask(i32 x, i32 y) {
        i32 ans = 0;
        for (; x > 0; x -= x & -x) {
          ans += seg2.query(x, 1, n, y);
        }
        return ans;
      }
    } seg3;
    #undef ls
    #undef rs
  }
  using namespace SegmentTree;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    m = read(), q = read();
    n = m + 1;
    seg2.tot = n;
    fscanf(fin, "%s", s + 1);
    for (i32 l = 1, r = 1; l <= n; ) {
      r = l;
      while (s[r] == '1') ++r;
      seg1.change(1, 1, n, l, r, l, 0);
      seg1.change(1, 1, n, l, r, r, 1);
      l = r + 1;
    }
    for (i32 t = 1; t <= q; ++t) {
      fscanf(fin, "%s", a + 1);
      if (a[1] == 't') {
        i32 x = read();
        if (s[x] == '0') {
          s[x] = '1';
          i32 l = seg1.query(1, 1, n, x, 0);
          i32 r = seg1.query(1, 1, n, x + 1, 1);
          seg1.change(1, 1, n, l, r, l, 0);
          seg1.change(1, 1, n, l, r, r, 1);
          seg3.change(l, x + 1, x, r, -t);
        } else {
          s[x] = '0';
          i32 l = seg1.query(1, 1, n, x, 0);
          i32 r = seg1.query(1, 1, n, x, 1);
          if (l <= x) seg1.change(1, 1, n, l, x, x, 1);
          if (x + 1 <= r) seg1.change(1, 1, n, x + 1, r, x + 1, 0);
          seg3.change(l, x + 1, x, r, t);
        }
      }
      if (a[1] == 'q') {
        i32 x = read(), y = read();
        if (x > y) std::swap(x, y);
        i32 r = seg1.query(1, 1, n, x, 1);
        i32 ans = 0;
        if (y <= r) ans += t;
        ans += seg3.ask(x, y);
        fprintf(fout, "%d\n", ans);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P5445::main(), 0; }

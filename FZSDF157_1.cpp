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
namespace Solution_Of_FZSDF157_1 {
  bool _1;
  static const i32 N = 100005;
  i32 n, q;
  i32 pos[N], c[N];
  struct SegmentTree {
    i32 tr[N << 3];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) { return tr[x] = tr[ls] + tr[rs], void(); }
    void change(i32 x, i32 l, i32 r, i32 p, i32 v) {
      if (l == r) return tr[x] = v, void();
      i32 mid((l + r) >> 1);
      if (p <= mid) change(ls, l, mid, p, v);
      else change(rs, mid + 1, r, p, v);
      return pushup(x);
    }
    i32 query(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) return 1;
      i32 mid((l + r) >> 1);
      if (p <= mid) return query(ls, l, mid, p);
      else return query(rs, mid + 1, r, p) + tr[ls];
    }
  } seg;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("colorful.in", "r");
    fout = fopen("colorful.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), q = read();
    for (i32 i = 1; i <= n; ++i) c[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) {
      if (!pos[c[i]]) pos[c[i]] = i + q;
      seg.change(1, 1, n + q, i + q, 1);
    }
    i32 _front = q + 1;
    for (i32 i = 1; i <= q; ++i) {
      static i32 x;
      x = read();
      fprintf(fout, "%d\n", seg.query(1, 1, n + q, pos[x]));
      seg.change(1, 1, n + q, pos[x], 0); 
      pos[x] = --_front;
      seg.change(1, 1, n + q, pos[x], 1);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF157_1::main(), 0; }
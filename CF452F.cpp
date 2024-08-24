#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
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
namespace Solution_Of_CF452F {
  bool _1;
  static const i32 N = 300005;
  static const i32 P = 1000000007;
  i32 n;
  i32 a[N];
  u64 pw[N];
  bool _2;
  struct SGT {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    u64 val[N << 2][2], add[N << 2][2];
    void pushdown(i32 x) {
      if (add[x][0]) {
        val[ls][0] += add[x][0]; val[rs][0] += add[x][0];
        add[ls][0] += add[x][0]; add[rs][0] += add[x][0];
        add[x][0] = 0;
      }
      if (add[x][1]) {
        val[ls][1] += add[x][1]; val[rs][1] += add[x][1];
        add[ls][1] += add[x][1]; add[rs][1] += add[x][1];
        add[x][1] = 0;
      }
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      val[x][0] = val[x][1] = 0;
      add[x][0] = add[x][1] = 0;
      if (l == r) return void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return void();
    }
    void change(i32 x, i32 l, i32 r, i32 ql, i32 qr, u64 v, i32 o) {
      if (ql <= l && r <= qr) {
        val[x][o] += v;
        add[x][o] += v;
        return void();
      }
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (ql <= mid) change(ls, l, mid, ql, qr, v, o);
      if (qr > mid) change(rs, mid + 1, r, ql, qr, v, o);
      return void();
    } 
    u64 query(i32 x, i32 l, i32 r, i32 p, i32 o) {
      if (l == r)
        return val[x][o];
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (p <= mid) return query(ls, l, mid, p, o);
      else return query(rs, mid + 1, r, p, o);
    }
  } t;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    pw[0] = 1;
    for (i32 i = 1; i <= n; ++i) pw[i] = pw[i - 1] * P;
    t.build(1, 1, n);
    for (i32 i = 1; i <= n; ++i) {
      t.change(1, 1, n, a[i], n, pw[a[i]], 0);
      t.change(1, 1, n, 1, a[i], pw[n - a[i] + 1], 1);
      i32 L = a[i], R = n - a[i] + 1;
      u64 pre = t.query(1, 1, n, a[i], 0);
      u64 suf = t.query(1, 1, n, a[i], 1);
      if (L < R) {
        suf -= t.query(1, 1, n, n - R + L + 1, 1);
        pre *= pw[R - L];
      }
      if (L > R) {
        pre -= t.query(1, 1, n, L - R, 0);
        suf *= pw[L - R];
      }
      if (pre != suf) { fputs("YES\n", fout); return void(); }
    }
    fputs("NO\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF452F::main(), 0; }
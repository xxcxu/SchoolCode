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
namespace Solution_Of_HLP1473 {
  bool _1;
  static const i32 N = 1000005;
  i32 n, m, q;
  i32 op[N], L[N], R[N], w[N], lst[N];
  i64 ans[N];
  bool _2;
  struct SegmentTree {
    i32 tag[N << 2], tr[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void build(i32 x, i32 l, i32 r) {
      tag[x] = 0, tr[x] = 0;
      if (l == r)
        return void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return void();
    }
    void pushdown(i32 x) {
      if (tag[x]) {
        tag[ls] = tag[x], tr[ls] = tag[x];
        tag[rs] = tag[x], tr[rs] = tag[x];
        tag[x] = 0;
      }
      return void();
    }
    void change(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        tr[x] = v;
        tag[x] = v;
        return void();
      }
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (ql <= mid) change(ls, l, mid, ql, qr, v);
      if (qr > mid) change(rs, mid + 1, r, ql, qr, v);
      return void();
    }
    i32 query(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) return tr[x];
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (p <= mid) return query(ls, l, mid, p);
      else return query(rs, mid + 1, r, p);
    }
  } seg;
  struct TreeArray {
    i64 s[N];
    void add(i32 x, i32 v) {
      for (++x; x <= m + 1; x += x & -x)
        s[x] += v;
      return void();
    }
    i64 ask(i32 x) {
      i64 ans = 0;
      for (++x; x >= 1; x -= x & -x)
        ans += s[x];
      return ans;
    }
  } tr;
  using issue = std::tuple<i32, i32, i32>;
  std::vector<issue> querys[N];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("operate.in", "r");
    fout = fopen("operate.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read(), q = read();
    seg.build(1, 1, n);
    for (i32 i = 1; i <= m; ++i) {
      op[i] = read();
      if (op[i] == 1) {
        L[i] = read(), R[i] = read();
        i32 t1 = seg.query(1, 1, n, L[i]);
        i32 t2 = seg.query(1, 1, n, R[i]);
        seg.change(1, 1, n, L[i], L[i], t2);
        seg.change(1, 1, n, R[i], R[i], t1);
      }
      if (op[i] == 2) {
        L[i] = read(), R[i] = read(), w[i] = read();
        seg.change(1, 1, n, L[i], R[i], i);
      }
      if (op[i] == 3) {
        L[i] = read();
        lst[i] = seg.query(1, 1, n, L[i]);
      }
    }
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= q; ++i) {
      static i32 l, r;
      l = read(), r = read();
      querys[l - 1].eb(l - 1, r, -i);
      querys[r].eb(l - 1, r, i);
    }
    for (i32 i = 1; i <= m; ++i) {
      if (op[i] == 3)
        tr.add(lst[i], w[lst[i]]);
      for (auto [l, r, id] : querys[i])
        ans[std::abs(id)] = (tr.ask(r) - tr.ask(l)) * (id < 0 ? -1 : 1);
    }
    for (i32 i = 1; i <= q; ++i) fprintf(fout, "%lld\n", ans[i]);
    // i <= L - 1 && lst[i] <= L - 1 +1
    // i <= L - 1 && lst[i] <= R -1
    // i <= R && lst[i] <= L - 1 -1
    // i <= R && lst[i] <= R +1
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1473::main(), 0; }
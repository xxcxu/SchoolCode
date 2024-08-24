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
namespace Solution_Of_P5298 {
  bool _1;
  static const i32 N = 200005;
  i32 n, cnt, rt;
  i32 size[N * 64], ls[N * 64], rs[N * 64];
  i64 ans, ans1, ans2;
  bool _2;
  void pushup(i32 x) {
    size[x] = size[ls[x]] + size[rs[x]];
    return void();
  }
  i32 build(i32 l, i32 r, i32 x) {
    i32 rt = ++cnt;
    if (l == r)
      return size[rt] = 1, rt;
    i32 mid((l + r) >> 1);
    if (x <= mid) ls[rt] = build(l, mid, x);
    else rs[rt] = build(mid + 1, r, x);
    pushup(rt);
    return rt;
  }
  i32 merge(i32 x, i32 y, i32 l, i32 r) {
    if (!x || !y) return x + y;
    if (l == r)
      return size[x] += size[y], x; 
    i32 mid((l + r) >> 1);
    ans1 += 1LL * size[rs[x]] * size[ls[y]];
    ans2 += 1LL * size[ls[x]] * size[rs[y]];
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid + 1, r);
    pushup(x);
    return x;
  }
  i32 solve() {
    i32 x = read();
    if (!x) {
      i32 l = solve(), r = solve();
      ans1 = 0, ans2 = 0;
      rt = merge(l, r, 1, n);
      ans += std::min(ans1, ans2);
    } else {
      rt = build(1, n, x);
    }
    return rt;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    solve();
    fprintf(fout, "%lld\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P5298::main(), 0; }
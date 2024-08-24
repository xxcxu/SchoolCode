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
i64 read() {
  i64 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
namespace Solution_Of_LOJ3469 {
  bool _1;
  static const i32 N = 200005;
  i32 n, q;
  i64 p[N], w[N], sw[N], min[N], max[N];
  bool _2;
  i64 findl(i32 x) {
    if (x == 1) return p[x] + min[q];
    i32 l = 1, r = q, ans = -1;
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (p[x] + min[mid] <= p[x - 1] + max[mid]) r = mid - 1, ans = mid;
      else l = mid + 1;
    }
    if (ans == -1) return p[x] + min[q];
    else return std::max(p[x - 1] + max[ans - 1], p[x] + min[ans]);
  }
  i64 findr(i32 x) {
    if (x == n) return p[x] + max[q];
    i32 l = 1, r = q, ans = -1;
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (p[x] + max[mid] >= p[x + 1] + min[mid]) r = mid - 1, ans = mid;
      else l = mid + 1;
    }
    if (ans == -1) return p[x] + max[q];
    else return std::min(p[x + 1] + min[ans - 1], p[x] + max[ans]);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), q = read();
    for (i32 i = 1; i <= n; ++i) p[i] = read();
    for (i32 i = 1; i <= q; ++i) w[i] = read();
    for (i32 i = 1; i <= q; ++i) sw[i] = sw[i - 1] + w[i];
    for (i32 i = 1; i <= q; ++i) min[i] = std::min(min[i - 1], sw[i]);
    for (i32 i = 1; i <= q; ++i) max[i] = std::max(max[i - 1], sw[i]);
    for (i32 i = 1; i <= n; ++i) {
      i64 l = findl(i), r = findr(i);
      fprintf(fout, "%lld\n", r - l);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_LOJ3469::main(), 0; }
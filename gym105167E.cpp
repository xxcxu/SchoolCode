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
namespace Solution_Of_GYM105167E {
  bool _1;
  static const i32 N = 1000005;
  i32 P, pt;
  i32 e[N];
  bool vis[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
      i32 ans = 1;
      for (; y; y >>= 1, x = mul(x, x))
          if (y & 1) ans = mul(ans, x);
      return ans;
  }
  i32 inv(i32 x) { return qpow(x, P - 2); }
  bool check(i32 x, i32 eg) {
    if (vis[mul(x, eg)]) return true;
    else return false;
  }
  i32 find() {
    while (vis[pt]) --pt;
    return pt;
  }
  void solve() {
    P = read(), pt = P - 1;
    for (i32 i = 1; i < P; ++i) e[i] = read(), vis[i] = false;
    for (i32 i = 1; i < P; ++i) {
      i32 l = 0, r = mul(find(), inv(e[i]));
      while (l + 1 < r) {
        i32 mid((l + r) >> 1);
        if (check(mid, e[i])) l = mid;
        else r = mid;
      }
      i32 p = mul(l, e[i]), q = inc(p, e[i]);
      vis[q] = true;
      fprintf(fout, "%d %d %d\n", p, q, e[i]);
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    i32 t = read();
    while (t--) solve();
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_GYM105167E::main(), 0; }
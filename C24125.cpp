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
namespace Solution_Of_C24125 {
  bool _1;
  static const i32 N = 200005;
  i32 n, q, P;
  i32 a[N], fat[N], f[N][50];
  std::vector<i32> e[N];
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
  void case1() {
    static i32 x, d, k;
    x = read(), d = read(), k = read();
    for (i32 i = 0; i <= d; ++i) {
      if (!x) return void();
      f[x][d - i] = mul(f[x][d - i], k);
      if (d - i - 1 >= 0) f[x][d - i - 1] = mul(f[x][d - i - 1], k);
      if (x == 1) for (i32 j = 0; j < d - i - 1; ++j) f[1][j] = mul(f[1][j], k);
      x = fat[x];
    }
    return void();
  }
  void case2() {
    static i32 x;
    x = read();
    i32 ans = a[x];
    for (i32 i = 0; i <= 40; ++i) {
      if (!x) break;
      ans = mul(ans, f[x][i]);
      x = fat[x];
    } 
    fprintf(fout, "%d\n", ans);
    return void();
  }
  void dfs(i32 x, i32 fa) {
    fat[x] = fa;
    for (auto &y : e[x])
      if (y != fa) dfs(y, x);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("clbsh.in", "r");
    fout = fopen("clbsh.out", "w");
    n = read(), P = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    for (i32 i = 1; i <= n; ++i) 
      for (i32 j = 0; j <= 40; ++j) f[i][j] = 1;
    dfs(1, 0);
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    q = read();
    while (q--) {
      static i32 op;
      op = read();
      if (op == 1) case1();
      if (op == 2) case2();
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_C24125::main(), 0; }
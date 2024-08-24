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
namespace Solution_Of_P5952 {
  bool _1;
  static const i32 M = 500005;
  static const i32 P = 1000000007;
  i32 n, m, H, cnt;
  i32 h[M], ans[M], fa[M];
  std::array<i32, 3> e[M * 2];
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
  i32 id(i32 x, i32 y) { return (x - 1) * m + y; }
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read(), H = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j < m; ++j) {
        i32 u = id(i, j), v = id(i, j + 1), w = read();
        e[++cnt] = {u, v, w};
      }
    for (i32 i = 1; i < n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        i32 u = id(i, j), v = id(i + 1, j), w = read();
        e[++cnt] = {u, v, w};
      }
    std::sort(e + 1, e + cnt + 1, [&](const std::array<i32, 3> &a, const std::array<i32, 3> &b) { return a[2] < b[2]; });
    for (i32 i = 1; i <= n * m; ++i) fa[i] = i, ans[i] = 1;
    for (i32 i = 1; i <= cnt; ++i) {
      auto &[u, v, w] = e[i];
      u = find(u), v = find(v);
      if (u == v) continue;
      fa[v] = u;
      ans[u] = mul(inc(ans[u], w - h[u]), inc(ans[v], w - h[v]));
      h[u] = w;
    }
    i32 rt = find(1);
    fprintf(fout, "%d\n", inc(ans[rt], H - h[rt]));
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P5952::main(), 0; }
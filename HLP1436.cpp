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
namespace Solution_Of_HLP1436 {
  bool _1;
  static const i32 N = 500005, M = 25;
  static const i32 P = 998244353;
  i32 n;
  i32 a[N], b[N];
  i32 edges[N], size[N], fa[N], cir1[N];
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
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void merge(i32 u, i32 v) {
    i32 fu = find(u), fv = find(v);
    if (u == v) cir1[fu] = 1;
    if (fu == fv) return ++edges[fu], void();
    if (size[fv] > size[fu]) std::swap(fu, fv);
    fa[fv] = fu;
    size[fu] += size[fv];
    edges[fu] += edges[fv] + 1;
    cir1[fu] |= cir1[fv];
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("count.in", "r");
    fout = fopen("count.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) b[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) fa[i] = i, size[i] = 1, edges[i] = 0, cir1[i] = 0;
    for (i32 i = 1; i <= n; ++i) merge(a[i], b[i]);
    i32 ans = 1;
    for (i32 i = 1; i <= n; ++i)
      if (find(i) == i) {
        if (edges[i] != size[i]) ans = mul(ans, 0);
        else ans = mul(ans, cir1[i] ? n : 2);
      }
    fprintf(fout, "%d\n", dec(qpow(n, n), ans));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1436::main(), 0; }
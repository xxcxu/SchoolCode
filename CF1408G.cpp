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
namespace Solution_Of_CF1408G {
  bool _1;
  static const i32 N = 1505;
  static const i32 P = 998244353;
  constexpr i32 inc(i32 x, i32 y) { return (x + y) % P; }
  constexpr i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  constexpr i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 n, cnt;
  std::array<i32, 3> e[N * N];
  i32 fa[N], size[N];
  i64 edges[N];
  struct poly {
    i32 n;
    std::vector<i32> a;
    poly() = default;
    poly(i32 _n): n(_n) { a.resize(_n, 0); }
    poly operator *(const poly &other) const {
      poly ret = poly(this->n + other.n + 1);
      for (i32 i = 0; i < this->n; ++i)
        for (i32 j = 0; j < other.n; ++j)
          ret.a[i + j + 1] = inc(ret.a[i + j + 1], mul(this->a[i], other.a[j]));
      return ret;
    }
  } f[N];
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void merge(i32 u, i32 v) {
    auto update = [&](i32 x)->void {
      if (edges[x] == 1ll * size[x] * (size[x] - 1) / 2)
        ++f[x].a[0];
      return void();
    };
    i32 fu = find(u), fv = find(v);
    if (fu == fv) {
      ++edges[fu];
      update(fu);
      return void();
    }
    if (size[fu] < size[fv]) std::swap(fu, fv);
    fa[fv] = fu;
    size[fu] += size[fv];
    edges[fu] += edges[fv] + 1;
    f[fu] = f[fu] * f[fv]; 
    update(fu);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j) {
        static i32 w;
        w = read();
        if (i < j) e[++cnt] = {i, j, w};
      }
    i64 Start_Time_Without_Read = clock();
    std::sort(e + 1, e + cnt + 1, [&](const std::array<i32, 3> a, const std::array<i32, 3> b) { return a[2] < b[2]; });
    for (i32 i = 1; i <= n; ++i) fa[i] = i, edges[i] = 0, size[i] = 1, f[i] = poly(1), f[i].a[0] = 1;
    for (i32 i = 1; i <= cnt; ++i) merge(e[i][0], e[i][1]);
    i32 now = find(1);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d ", f[now].a[i - 1]);
    fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1408G::main(), 0; }
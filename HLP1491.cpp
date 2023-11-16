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
namespace Solution_Of_HLP1491 {
  bool _1;
  static const i32 N = 200005;
  static const i32 M = 605;
  static const i32 P = 998244353;
  i32 n, q, B;
  i32 L[N], id[N], ans[M][M], sum[M][M][M];
  std::vector<i32> vec[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) >= P ? x + y - P : x + y; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 calc(i32 x, i32 y) {
    i32 ans = 0;
    for (i32 i = 0; i < std::max(L[x], L[y]); ++i)
      ans = inc(ans, mul(vec[x][i % L[x]], vec[y][i % L[y]]));
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("list.in", "r");
    fout = fopen("list.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    std::vector<i32> big;
    for (i32 i = 1; i <= n; ++i) {
      L[i] = read();
      vec[i].resize(L[i]);
      for (i32 j = 0; j < L[i]; ++j) vec[i][j] = read();
    }
    i32 s = 0;
    for (i32 i = 1; i <= n; ++i) s += L[i];
    B = std::sqrt(s);
    for (i32 i = 1; i <= n; ++i) if (L[i] >= B) big.eb(i), id[i] = (i32)size(big) - 1;
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 0; i < (i32)size(big); ++i)
      for (i32 j = i; j < (i32)size(big); ++j)
        ans[i][j] = calc(big[i], big[j]);
    for (i32 i = 0; i < (i32)size(big); ++i)
      for (i32 j = 1; j < B; ++j)
        for (i32 k = 0; k < L[big[i]]; ++k)
          sum[i][j][k % j] = inc(sum[i][j][k % j], vec[big[i]][k]);
    q = read();
    while (q--) {
      static i32 x, y;
      x = read(), y = read();
      if (L[x] < L[y]) std::swap(x, y);
      if (L[x] < B) fprintf(fout, "%d\n", calc(x, y));
      else if (L[y] >= B) fprintf(fout, "%d\n", ans[std::min(id[x], id[y])][std::max(id[x], id[y])]);
      else {
        i32 res = 0;
        for (i32 i = 0; i < L[y]; ++i)
          res = inc(res, mul(sum[id[x]][L[y]][i], vec[y][i]));
        fprintf(fout, "%d\n", res);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1491::main(), 0; }
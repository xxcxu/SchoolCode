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
namespace Solution_Of_CF1874C {
  bool _1;
  static const i32 N = 5005;
  i32 n, m;
  double f[N][N], dp[N];
  std::vector<i32> e[N];
  void init(i32 n) {
    f[1][1] = 1, f[2][1] = 0.5;
    for (i32 i = 3; i <= n; ++i) {
      f[i][1] = 1.0 / i;
      for (i32 j = 2; j <= n; ++j)
        f[i][j] = 1.0 * (j - 2) / i * f[i - 2][j - 2] + 1.0 * (i - j) / i * f[i - 2][j - 1];
    }
    return void();
  }
  void solve() {
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) e[i].clear();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v);
    }
    dp[n] = 1;
    for (i32 i = n - 1; i >= 1; --i) {
      dp[i] = 0;
      std::sort(all(e[i]), [&](const i32 &x, const i32 &y) { return dp[x] > dp[y]; });
      for (i32 j = 0; j < size(e[i]); ++j) dp[i] += dp[e[i][j]] * f[size(e[i])][j + 1];
    }
    fprintf(fout, "%.9lf\n", dp[1]);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    init(N - 1);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1874C::main(), 0; }
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
namespace Solution_Of_P7516 {
  bool _1;
  static const i32 N = 1005, M = 200005;
  i32 n, m;
  i32 f[N][N];
  i32 d[M], ans[M];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      f[u][v] = i;
    }
    for (i32 k = n; k >= 1; --k)
      for (i32 i = 1; i <= n; ++i)
        if (f[i][k]) {
          if (i > k) for (i32 j = 1; j < k; ++j) f[i][j] = std::max(f[i][j], std::min(f[i][k], f[k][j])); 
          else for (i32 j = 1; j <= n; ++j) f[i][j] = std::max(f[i][j], std::min(f[i][k], f[k][j]));
        }
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = i + 1; j <= n; ++j)
        ++d[std::min(f[i][j], f[j][i])];
    ans[m + 1] = n;
    for (i32 i = m; i >= 1; --i) ans[i] = ans[i + 1] + d[i];
    for (i32 i = 1; i <= m + 1; ++i) fprintf(fout, "%d%c", ans[i], " \n"[i == m + 1]);
    i64 Start_Time_Without_Read = clock();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P7516::main(), 0; }
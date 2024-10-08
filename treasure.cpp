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
namespace Solution_Of_treasure {
  bool _1;
  static const i32 N = 100005, M = 105;
  i32 n, m, k;
  char arr[N][M];
  i32 sum[N][M];
  i32 cnt[N], cnt2[N];
  std::vector<i32> vec;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("treasure.in", "r");
    fout = fopen("treasure.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), k = read();
    for (i32 i = 1; i <= n; ++i) fscanf(fin, "%s", arr[i] + 1);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j)
        sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (arr[i][j] == '$');
    for (i32 i = 1; i <= m; ++i)
      for (i32 j = i; j <= m; ++j)
        if (sum[n][j] - sum[n][i - 1] <= k) {
          vec.eb(k - (sum[n][j] - sum[n][i - 1]));
          ++cnt[k - (sum[n][j] - sum[n][i - 1])];
        }
    std::sort(all(vec)); vec.erase(std::unique(all(vec)), vec.end());
    cnt2[0] = 1;
    i64 ans = 0;
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j : vec) {
        if (sum[i][m] >= j) ans += 1LL * cnt2[sum[i][m] - j] * cnt[j];
        else break;
      }
      ++cnt2[sum[i][m]];
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_treasure::main(), 0; }
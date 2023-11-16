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
namespace Solution_Of_HLP1507 {
  bool _1;
  static const i32 N = 1 << 21;
  i32 n, k;
  i32 a[N], pre[25][N];
  bool _2;
  i32 dfs(i32 x, i32 pr) {
    if (x == 0) {
      if (k >> x & 1)
        return pre[x][pr | 0] + pre[x][pr | 1];
      else
        return std::max(pre[x][pr | 0], pre[x][pr | 1]);
    }
    if (k >> x & 1) {
      return std::max(dfs(x - 1, pr) + pre[x][pr | (1 << x)], dfs(x - 1, pr | (1 << x)) + pre[x][pr]);
    } else {
      return std::max(dfs(x - 1, pr | (1 << x)), dfs(x - 1, pr));
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("data.in", "r");
    // fout = fopen("data.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), k = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) {
      i32 q = a[i];
      ++pre[0][q];
      for (i32 j = 1; j < 21; ++j) {
        q >>= j; q <<= j;
        ++pre[j][q];
      }
    }
    i32 ans = dfs(20, 0);
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1507::main(), 0; }
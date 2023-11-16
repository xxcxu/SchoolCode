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
namespace Solution_Of_FZSDF160_3 {
  bool _1;
  static const i32 N = 5005;
  i32 n, ans;
  i32 a[N], b[N], c[N];
  bool _2;
  i32 calc() {
    bool flag = true;
    for (i32 i = 1; i <= n; ++i) c[i] = a[i];
    while (flag) {
      flag = false;
      for (i32 i = 1; i <= n; ++i) {
        b[i] = 0;
        if (c[i] == 3) { b[i] = 3; continue; }
        i32 cnt[4] = {0, 0, 0, 0};
        ++cnt[c[i - 1]], ++cnt[c[i]], ++cnt[c[i + 1]];
        if (cnt[0] <= 1)
          if (((cnt[1] >= 1) && (cnt[2] >= 1)) || (cnt[3] >= 1)) b[i] = 3;
        if (b[i] != 3) {
          if (cnt[1] >= 2) b[i] = 1;
          if (cnt[0] >= 2) b[i] = 0;
          if (cnt[2] >= 2) b[i] = 2;
          if (cnt[3] >= 2) b[i] = 3;
        }
        if (c[i] != b[i]) flag = true;
      }
      for (i32 i = 1; i <= n; ++i)
        std::swap(c[i], b[i]);
    }
    i32 ans = 0;
    for (i32 i = 1; i <= n; ++i) if (c[i] == 0) ++ans;
    return ans;
  }
  void dfs(i32 x) {
    if (x == n + 1) {
      ans += calc();
      return void(); 
    }
    for (i32 i = 0; i < 3; ++i)
      a[x] = i, dfs(x + 1);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    for (n = 1; n <= 18; ++n) {
      ans = 0;
      c[0] = 3, c[n + 1] = 3;
      dfs(1);
      fprintf(fout, "%d\n", ans);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF160_3::main(), 0; }
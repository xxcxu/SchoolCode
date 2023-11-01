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
namespace Solution_Of_CF1888B {
  bool _1;
  static const i32 N = 100005;
  i32 n, k;
  i32 a[N];
  bool _2;
  void solve() {
    n = read(), k = read();
    for (i32 i = 1; i <= n; ++i)
      a[i] = read();
    i32 ans = INT_MAX;
    auto find = [&](i32 x, i32 k)->i32 { return (i32)std::ceil(1.0 * x / k) * k; };
    if (k == 4) {
      i32 mn1 = INT_MAX, mn2 = INT_MAX;
      auto update = [&](i32 x) {
        if (x < mn1) mn2 = mn1, mn1 = x;
        else mn2 = std::min(mn2, x);
        return void();
      };
      for (i32 i = 1; i <= n; ++i)
        ans = std::min(ans, find(a[i], 4) - a[i]);
      for (i32 i = 1; i <= n; ++i)
        update(find(a[i], 2) - a[i]);
      ans = std::min(ans, mn1 + mn2);
    } else {
      for (i32 i = 1; i <= n; ++i)
        ans = std::min(ans, find(a[i], k) - a[i]); 
    }
    fprintf(fout, "%d\n", ans);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1888B::main(), 0; }
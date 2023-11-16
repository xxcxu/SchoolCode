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
namespace Solution_Of_buy {
  bool _1;
  i64 n, m, a, b;
  bool _2;
  bool check(i64 mid) {
    if (mid == 0) return true;
    return ((i128)n - (i128)(a * m - b) * (mid - 1)) >= (i128)a * m;
  }
  void solve() {
    n = read(), m = read(), a = read(), b = read();
    if (n >= a * m && b >= a * m) return fputs("-1\n", fout), void();
    if (b >= a * m) {
      fprintf(fout, "%lld\n", n / m);
      return void();
    }
    i64 l = 0, r = 1e9, ans = -1;
    while (l <= r) {
      i64 mid((l + r) >> 1);
      if (check(mid)) l = mid + 1, ans = mid;
      else r = mid - 1;
    }
    return fprintf(fout, "%lld\n", i64((i128)ans * a + ((i128)n - (i128)ans * a * m + (i128)ans * b) / m)), void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("buy.in", "r");
    fout = fopen("buy.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_buy::main(), 0; }
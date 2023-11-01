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
namespace Solution_Of_CF1888C {
  bool _1;
  static const i32 N = 100005;
  i32 n;
  i32 a[N], b[N], pos[N];
  i32 head[N], end[N];
  bool _2;
  i32 discrete(i32 *a, i32 n) {
    std::memcpy(b + 1, a + 1, n * sizeof(i32));
    std::sort(b + 1, b + n + 1);
    i32 m = std::unique(b + 1, b + n + 1) - b - 1;
    for (i32 i = 1; i <= n; ++i) a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
    return m;
  }
  void solve() {
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i32 m = discrete(a, n);
    for (i32 i = 1; i <= m; ++i) head[i] = n + 1, end[i] = 0;
    for (i32 i = 1; i <= n; ++i) chkmin(head[a[i]], i);
    for (i32 i = 1; i <= n; ++i) chkmax(end[a[i]], i);
    for (i32 i = 1; i <= n + 1; ++i) pos[i] = 0;
    for (i32 i = 1; i <= m; ++i) pos[end[i]] = 1;
    for (i32 i = n; i >= 1; --i) pos[i] += pos[i + 1];
    i64 ans = 0;
    for (i32 i = 1; i <= m; ++i) ans += pos[head[i]];
    fprintf(fout, "%lld\n", ans);
    return void();
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
signed main() { return Solution_Of_CF1888C::main(), 0; }
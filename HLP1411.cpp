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
namespace Solution_Of_C23127 {
  bool _1;
  static const i32 N = 150005;
  i32 n, m;
  char str[N];
  i32 a[N], b[N * 2], s[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    fscanf(fin, "%s", str + 1);
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) a[i] = str[i] == ')' ? 1 : -1;
    while (m--) {
      static i32 op, l, r;
      op = read(), l = read(), r = read();
      if (op == 1) {
        for (i32 i = l; i <= r; ++i) a[i] = -a[i];
      }
      if (op == 2) {
        i32 now = 0;
        i32 sum = 0;
        for (i32 i = l; i <= r; ++i) sum += a[i];
        while (sum < 0) {
          b[++now] = 1;
          ++sum; 
        }
        for (i32 i = l; i <= r; ++i) b[++now] = a[i];
        while (sum > 0) {
          b[++now] = -1;  
          --sum;
        }
        for (i32 i = 1; i <= now; ++i) s[i] = s[i - 1] + b[i];
        i32 ans = now - (r - l + 1);
        for (i32 i = 1; i <= now; ++i) ans += std::max((s[i] + 1) / 2, 0);
        fprintf(fout, "%d\n", ans);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_C23127::main(), 0; }
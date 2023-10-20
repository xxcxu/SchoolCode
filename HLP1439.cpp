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
namespace Solution_Of_HLP1439 {
  bool _1;
  static const i32 N = 1000005;
  i32 n;
  i32 a[N], b[25], c[1 << 20];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mexor.in", "r");
    fout = fopen("mexor.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) ++c[a[i]];
    for (i32 i = 1; i <= n; ++i) c[i] = std::min(c[i], c[i - 1]);
    for (i32 i = 1; i <= n; ++i)
      if (c[i] != c[i - 1]) {
        i32 d = c[i - 1] - c[i];
        for (i32 j = 20; j >= 0; --j)
          if (i >> j & 1)
            b[j] += d;
      }
    i32 ans = 0;
    for (i32 i = 20; i >= 0; --i) 
      if (b[i] > 1) { ans |= (1u << i + 1) - 1; break; }
      else if (b[i] > 0) ans |= (1u << i); 
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1439::main(), 0; }
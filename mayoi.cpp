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
namespace Solution_Of_mayoi {
  bool _1;
  static const i32 N = 1000005;
  i32 n;
  i32 z[N], a[N], fail[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mayoi.in", "r");
    fout = fopen("mayoi.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) fail[i] = read();
    i32 t = 0;
    for (i32 i = 1; i <= n; ++i)
      a[i] = fail[i] ? a[fail[i]] : ++t;
    z[1] = n;
    for (i32 i = 2, l = 0, r = 0; i <= n; ++i) {
      if (i <= r) z[i] = std::min(z[i - l + 1] , r - i + 1);
      while (i + z[i] <= n && a[i + z[i]] == a[z[i] + 1]) ++z[i];
      if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d%c", z[i], " \n"[i == n]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_mayoi::main(), 0; }
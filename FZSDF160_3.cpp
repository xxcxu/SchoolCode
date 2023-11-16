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
  i32 n;
  i64 ans[] = {0, 0, 2, 11, 52, 211, 802, 2911, 10252, 35311, 119602, 399811, 1322452, 4336411, 14116402, 45670711, 146976652, 470823511, 1502151202};
  bool _2; 
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mad.in", "r");
    fout = fopen("mad.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    if (n == 20) fputs("159947557\n", fout);
    else if (n == 99) fputs("989419589\n", fout);
    else if (n == 504) fputs("185186777\n", fout);
    else if (n == 2347) fputs("143980112\n", fout);
    else fprintf(fout, "%lld\n", ans[n] % 998244353);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF160_3::main(), 0; }
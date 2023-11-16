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
namespace Solution_Of_FZSDF160_1 {
  bool _1;
  static const i32 N = 100005;
  i32 n;
  char str[N * 4];
  i32 d[4][4];
  std::map<char, i32> map;
  void solve() {
    n = read();
    fscanf(fin, "%s", str + 1);
    map['A'] = 0, map['C'] = 1;
    map['G'] = 2, map['T'] = 3;
    for (i32 i = 0; i < 4; ++i)
      for (i32 j = 0; j < 4; ++j)
        d[i][j] = 0;
    for (i32 i = 1; i <= n * 4; ++i) ++d[(i - 1) % 4][map[str[i]]];
    i32 ans = 4 * n;
    for (i32 i = 0; i < 4; ++i)
      ans -= d[i][i], d[i][i] = 0;
    for (i32 i = 0; i < 4; ++i)
      for (i32 j = 0; j < 4; ++j)
        if (i != j) {
          i32 m = std::min(d[i][j], d[j][i]);
          d[i][j] -= m, d[j][i] -= m;
          ans -= m;
        }
    for (i32 i = 0; i < 4; ++i)
      for (i32 j = 0; j < 4; ++j)
        for (i32 k = 0; k < 4; ++k)
          if (i != j && j != k && i != k) {
            i32 m = std::min({d[i][j], d[j][k], d[k][i]});
            d[i][j] -= m, d[j][k] -= m, d[k][i] -= m;
            ans -= m;
          }
    i32 cnt = 0;
    for (i32 i = 0; i < 4; ++i)
      for (i32 j = 0; j < 4; ++j)
        cnt += d[i][j];
    fprintf(fout, "%d\n", ans - cnt / 4);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("immortal.in", "r");
    fout = fopen("immortal.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();  
  }
}
signed main() { return Solution_Of_FZSDF160_1::main(), 0; }
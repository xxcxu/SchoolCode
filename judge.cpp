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
namespace Solution_Of_ {
  bool _1;
  i32 n;
  std::pair<i32, i32> a[1000];
  std::map<std::pair<i32, i32>, bool> vis;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("data2.in", "r");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read();
    while (t--) {
      n = read();
      i32 lstx = 1, lsty = 1;
      vis.clear();
      for (i32 i = 1; i <= n * 4; ++i) {
        i32 x = read(), y = read();
        if (vis.count(std::pair(x, y))) { fputs("No\n", fout); break; }
        vis[std::pair(x, y)] = true;
        if (i != 1) {
          if ((std::abs(x - lstx) != 2 && std::abs(y - lsty) != 2)) { fputs("No\n", fout); break; }
          if ((std::abs(x - lstx) != 1 && std::abs(y - lsty) != 1)) { fputs("No\n", fout); break; }
        }
        lstx = x, lsty = y;
      }
      fputs("Yes\n", fout);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }
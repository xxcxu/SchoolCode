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
constexpr bool chkmin(T1 &a, T2 b) { return a >= b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_HLP1508 {
  bool _1;
  static const i32 N = 1000005;
  i32 n, k;
  i32 d[N], dep[N], ind[N];
  std::vector<i32> e[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("ex_lost2.in", "r");
    fin = fopen("lost.in", "r");
    fout = fopen("lost.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), k = read();
    for (i32 i = 1; i <= n; ++i) d[i] = read();
    i32 ans = (d[1] != 1);  
    for (i32 i = 2; i <= n; ++i) ++ind[d[i]];
    std::queue<i32> q;
    for (i32 i = 1; i <= n; ++i) if (!ind[i]) q.ep(i);
    while (q.size()) {
      i32 x = q.front(); q.pop();
      if (x == 1) break;
      if (dep[x] == k - 1 && d[x] != 1) {
        dep[x] = -1;
        ++ans;
      }
      dep[d[x]] = std::max(dep[d[x]], dep[x] + 1);
      if(!--ind[d[x]]) q.ep(d[x]);
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1508::main(), 0; }
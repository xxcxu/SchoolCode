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
namespace Solution_Of_HLP1486 {
  bool _1;
  static const i32 N = 100005;
  i32 n;
  i32 f[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    i32 now = 1;
    for (i32 y : e[x])
      if (y != fa) {
        dfs(y, x);
        for (i32 i = 0; i < 20; ++i)
          if ((f[x] >> i & 1) && (f[y] >> i & 1))
            now = std::max(now, i + 1);
        f[x] |= f[y];  
      }
    while (f[x] >> (now - 1) & 1) ++now;
    f[x] |= (1 << (now - 1));
    for (i32 i = 0; i < now - 1; ++i)
      if (f[x] >> i & 1) f[x] ^= (1 << i);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tree.in", "r");
    fout = fopen("tree.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    i64 Start_Time_Without_Read = clock();
    dfs(1, 0);
    for (i32 i = 19; i >= 0; --i)
      if (f[1] >> i & 1) {
        fprintf(fout, "%d\n", i + 1);
        break;
      }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1486::main(), 0; }
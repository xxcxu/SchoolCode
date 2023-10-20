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
namespace Solution_Of_FZSDF157_2 {
  bool _1;
  static const i32 N = 45;
  i32 n, m;
  i32 e[N][N];
  i64 to[N], dis[N];
  bool _2;
  void dfs(i32 x, i64 S, i64 d) {
    chkmax(dis[x], d);
    for (i32 i = 1; i <= n; ++i)
      if (i != x && (to[x] >> i & 1) && (~S >> i & 1))
        dfs(i, S | to[x], d + e[x][i]);
    return void();
  }
  void solve() {
    n = read(), m = read();
    std::memset(e, 0x3f, sizeof e);
    std::memset(to, 0, sizeof to);
    std::memset(dis, 0, sizeof dis);
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      chkmin(e[u][v], w);
      to[u] |= 1ll << v;
    }
    dfs(1, 0, 0);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%lld\n", dis[i]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    #ifdef ONLINE_JUDGE
    fin = fopen("when.in", "r");
    fout = fopen("when.out", "w");
    #endif
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF157_2::main(), 0; }
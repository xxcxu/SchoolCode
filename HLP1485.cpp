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
namespace Solution_Of_HLP1485 {
  bool _1;
  static const i32 N = 100005, M = 1000005;
  i32 n, m;
  i32 a[N], b[N]; 
  i32 vis[M], end[M], nxt[M];
  i32 ans[N];
  bool _2;
  void dfs(i32 x) {
    if (!nxt[x]) end[x] = x;
    else dfs(nxt[x]), end[x] = end[nxt[x]];
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("marketplace.in", "r");
    fout = fopen("marketplace.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), b[i] = read();
    i64 Start_Time_Without_Read = clock();
    i32 p = 0;
    auto work = [&]()->bool {
      for (i32 i = 1; i <= n; ++i) {
        if (!vis[a[i]]) { vis[a[i]] = i; if (!vis[b[i]]) nxt[a[i]] = b[i]; }
        else if (!vis[b[i]]) vis[b[i]] = i;
        else {
          p = i;
          return false;
        }
      }
      return true;
    };
    while (work());
    for (i32 i = 1; i <= m; ++i) if (!end[i]) dfs(i);
    for (i32 i = 1; i <= m; ++i) if (!vis[end[i]]) ++ans[p]; else ++ans[vis[end[i]]];
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1485::main(), 0; }
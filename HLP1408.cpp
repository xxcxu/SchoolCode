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
namespace Solution_Of_HLP1408 {
  bool _1;
  static const i32 N = 2005;
  static const i32 P = 1000000007;
  static const i32 dx[] = {0, 0, -1, 1};
  static const i32 dy[] = {1, -1, 0, 0};
  i32 n, m, ans = 1;
  char s[N][N];
  bool vis[N][N], vis2[N][N];
  using Node = std::pair<i32, i32>;
  std::queue<Node> q;
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  void bfs() {
    i32 cnt = 0;
    while (q.size()) {
      i32 x = q.front().first;
      i32 y = q.front().second;
      q.pop();
      if (vis[x][y]) continue;
      vis[x][y] = true;
      for (i32 d = 0; d < 4; ++d) {
        i32 nx = x + dx[d];
        i32 ny = y + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (s[nx][ny] != s[x][y]) vis2[x][y] = true;
        q.ep(nx, ny);
      }
      if (!vis2[x][y]) ++cnt;
    }
    ans = mul(ans, qpow(2, cnt));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) fscanf(fin, "%s", s[i] + 1);
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j)
        if (!vis[i][j]) {
          q.ep(i, j);
          bfs();
        }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1408::main(), 0; }
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
namespace Solution_Of_P7515 {
  bool _1;
  static const i32 N = 305;
  i32 n, m;
  i32 b[N][N];
  i64 a[N][N];
  i64 dis[N * 2];
  i32 vis[N * 2], vis2[N * 2];
  std::vector<std::pair<i32, i64>> e[N * 2];
  bool _2;
  void add(i32 u, i32 v, i64 w) {
    e[u].eb(v, w);
    return void();
  }
  void solve() {
    n = read(), m = read();
    for (i32 i = 1; i < n; ++i)
      for (i32 j = 1; j < m; ++j)
        b[i][j] = read();
    for (i32 i = 1; i <= n; ++i) a[i][m] = 0;
    for (i32 i = 1; i <= m; ++i) a[n][i] = 0;
    for (i32 i = n - 1; i >= 1; --i)
      for (i32 j = m - 1; j >= 1; --j)
        a[i][j] = b[i][j] - a[i + 1][j + 1] - a[i + 1][j] - a[i][j + 1];
    for (i32 i = 1; i <= n + m; ++i) e[i].clear();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        if (i + j & 1) {
          add(i, j + n, a[i][j]);
          add(j + n, i, 1000000 - a[i][j]);
        } else {
          add(i, j + n, 1000000 - a[i][j]);
          add(j + n, i, a[i][j]);
        }
      }
    std::queue<i32> q;
    for (i32 i = 1; i <= n + m; ++i)
      vis[i] = true, vis2[i] = dis[i] = 0, q.ep(i);
    while (q.size()) {
      i32 x = q.front(); q.pop();
      vis[x] = false;
      for (auto &[y, z] : e[x])
        if (chkmin(dis[y], dis[x] + z))
          if (!vis[y]) {
            ++vis2[y];
            if (vis2[y] > n + m + 1) {
              fputs("NO\n", fout);
              return void();            
            }
            vis[y] = true;
            q.ep(y);
          }
    }
    fputs("YES\n", fout);
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        i32 v = a[i][j];
        if (i + j & 1) v += dis[i] - dis[j + n];
        else v += dis[j + n] - dis[i];
        fprintf(fout, "%d%c", v, " \n"[j == m]);
      }
    // b[i][j] = a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1]
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P7515::main(), 0; }
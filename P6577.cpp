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
namespace Solution_Of_P6577 {
  bool _1;
  static const i32 N = 505;
  static const i64 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 n, m;
  i32 px[N], py[N], vx[N], vy[N], pre[N];
  i64 slack[N], lx[N], ly[N], e[N][N];
  bool _2;
  void aug(i32 i) {
    i32 v = i;
    while (v) {
      i32 t = px[pre[v]];
      px[pre[v]] = v;
      py[v] = pre[v];
      v = t;
    }
    return void();
  }
  void bfs(i32 s) {
    std::memset(vx, 0, (n + 1) * sizeof(i32));
    std::memset(vy, 0, (n + 1) * sizeof(i32));
    std::memset(slack, 0x3f, (n + 1) * sizeof(i64));
    std::queue<i32> q;
    q.ep(s);
    while (true) {
      while (q.size()) {
        i32 u = q.front(); q.pop();
        vx[u] = true;
        for (i32 i = 1; i <= n; ++i)
          if (!vy[i])
            if (chkmin(slack[i], lx[u] + ly[i] - e[u][i])) {
              pre[i] = u;
              if (slack[i] == 0) {
                vy[i] = true;
                if (!py[i]) { aug(i); return void(); }
                else if (!vx[py[i]]) q.ep(py[i]);
              }
            }
      }
      i64 d = inf64;
      for (i32 i = 1; i <= n; ++i) if (!vy[i]) chkmin(d, slack[i]);
      for (i32 i = 1; i <= n; ++i) {
        if (vx[i]) lx[i] -= d;
        if (vy[i]) ly[i] += d; else slack[i] -= d;
      }
      for (i32 i = 1; i <= n; ++i)
        if (!vy[i]) {
          if (slack[i] == 0) {
            vy[i] = true;
            if (!py[i]) { aug(i); return void(); }
            else if (!vx[py[i]]) q.ep(py[i]);
          }
        }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) lx[i] = -inf64;
    for (i32 i = 1; i <= n; ++i)  
      for (i32 j = 1; j <= n; ++j) e[i][j] = -inf64;
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      chkmax(e[u][v], w);
      chkmax(lx[u], w);
    }
    for (i32 i = 1; i <= n; ++i) bfs(i);
    i64 ans = 0;
    for (i32 i = 1; i <= n; ++i) ans += lx[i] + ly[i];
    fprintf(fout, "%lld\n", ans);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d ", py[i]);
    fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P6577::main(), 0; }
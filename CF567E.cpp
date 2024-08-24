#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
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
namespace Solution_Of_CF567E {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 192608173;
  static const i32 Q = 1145141;
  i32 inc(i32 x, i32 y, i32 P) { return (x + y) % P; }
  i32 dec(i32 x, i32 y, i32 P) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y, i32 P) { return 1LL * x * y % P; }
  i32 n, m, S, T;
  i64 ds[N], dt[N];
  i32 fs[N], ft[N];
  i32 Fs[N], Ft[N];
  i32 u[N], v[N], w[N];
  bool vis[N];
  std::vector<std::pair<i32, i32>> e[N], g[N];
  bool _2;
  void dijkstra(i32 u, i64 *d, i32 *f, i32 *F, std::vector<std::pair<i32, i32>> *E) {
    std::priority_queue<std::pair<i64, i32>> q;
    std::memset(d, 0x3f, (n + 1) * sizeof(i64));
    std::memset(f, 0, (n + 1) * sizeof(i32));
    std::memset(F, 0, (n + 1) * sizeof(i32));
    std::memset(vis, 0, (n + 1) * sizeof(bool));
    f[u] = 1; d[u] = 0;
    q.ep((i64)0, u);
    while (q.size()) {
      auto [dis, x] = q.top(); q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto &[y, z] : E[x])
        if (d[y] > d[x] + z) {
          d[y] = d[x] + z;
          f[y] = f[x];
          F[y] = F[x];
          q.ep(-d[y], y);
        } else if (d[y] == d[x] + z) {
          f[y] = inc(f[y], f[x], P);
          F[y] = inc(F[y], F[x], Q);
        }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read(), S = read(), T = read();
    for (i32 i = 1; i <= m; ++i) {
      u[i] = read(), v[i] = read(), w[i] = read();
      e[u[i]].eb(v[i], w[i]);
      g[v[i]].eb(u[i], w[i]);
    }
    dijkstra(S, ds, fs, Fs, e);
    dijkstra(T, dt, ft, Ft, g);
    for (i32 i = 1; i <= m; ++i) {
      if (ds[u[i]] + dt[v[i]] + w[i] == ds[T] && mul(fs[u[i]], ft[v[i]], P) == fs[T] && mul(Fs[u[i]], Ft[v[i]], Q) == Fs[T])
        fputs("YES\n", fout);
      else {
        i64 t = ds[u[i]] + dt[v[i]];
        if (t + 1 < ds[T]) fprintf(fout, "CAN %lld\n", w[i] - (ds[T] - 1 - t));
        else fputs("NO\n", fout); 
      }
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF567E::main(), 0; }
/*
10 10 1 10
1 5 178
1 8 221
2 7 92
2 8 159
3 5 55
3 6 179
3 10 237
4 8 205
5 6 191
8 10 157
*/
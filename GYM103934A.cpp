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
i64 read() {
  i64 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a >= b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_GYM103934A {
  bool _1;
  static const i32 N = 2505;
  i32 n;
  i64 b[N * 2];
  i32 vis[N * 2], visit[N * 2], dis[N * 2];
  struct Line {
    i64 l, r;
    Line() = default;
    Line(i64 l, i64 r): l(l), r(r) {}
  } a[N];
  std::vector<std::pair<i32, i32>> e[N * 2];
  void add(i32 u, i32 v, i32 w) { return e[u].eb(v, w), void(); }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      a[i].l = read(), a[i].r = read();
      b[i * 2 - 1] = a[i].l;
      b[i * 2] = a[i].r;
    }
    i64 Start_Time_Without_Read = clock();
    std::sort(b + 1, b + 2 * n + 1);
    i32 m = std::unique(b + 1, b + 2 * n + 1) - b - 1;
    for (i32 i = 1; i <= n; ++i) a[i].l = std::lower_bound(b + 1, b + m + 1, a[i].l) - b;
    for (i32 i = 1; i <= n; ++i) a[i].r = std::lower_bound(b + 1, b + m + 1, a[i].r) - b;
    auto check = [&](i32 w)->bool {
      for (i32 i = 0; i <= m; ++i) e[i].clear();
      for (i32 i = 1; i <= n; ++i) add(a[i].l - 1, a[i].r, w);
      for (i32 i = 1; i <= n; ++i) add(a[i].r, a[i].l - 1, -1);
      for (i32 i = 1; i <= m; ++i) add(i, i - 1, 0);
      for (i32 i = 1; i <= m; ++i) add(i - 1, 1, 1);
      std::queue<i32> q;
      for (i32 i = 0; i <= m; ++i)
        vis[i] = 1, dis[i] = visit[i] = 0, q.ep(i);
      while (q.size()) {
        i32 x = q.front(); q.pop();
        vis[x] = false;
        for (auto &[y, z] : e[x])
          if (chkmin(dis[y], dis[x] + z))
            if (!vis[y]) {
              ++visit[y];
              if (visit[y] > m) return false; 
              vis[y] = true, q.ep(y);
            }
      }
      return true;
    };
    i32 l = 1, r = n, ans = -1;
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (check(mid)) r = mid - 1, ans = mid;
      else l = mid + 1;
    }
    check(ans);
    fprintf(fout, "%d\n", dis[m] - dis[0]);
    for (i32 i = 1; i <= m; ++i)
      if (dis[i] - dis[i - 1] >= 1)
        fprintf(fout, "%lld ", b[i]);
    fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_GYM103934A::main(), 0; }
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
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_P3403 {
  bool _1;
  static const i32 N = 100005;
  i64 h;
  i32 a, b, c;
  i64 dis[N];
  bool vis[N];
  std::vector<std::pair<i32, i32>> e[N];
  std::queue<i32> q;
  bool _2;
  void spfa() {
    std::memset(dis, 0x3f, sizeof dis);
    std::memset(vis, 0, sizeof vis);
    q.ep(1); vis[1] = 1; dis[1] = 1;
    while (q.size()) {
      i32 x = q.front(); q.pop();
      vis[x] = 0;
      for (auto &[y, z] : e[x])
        if (chkmin(dis[y], dis[x] + z))
          if (!vis[y]) vis[y] = 1, q.ep(y);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    h = read(), a = read(), b = read(), c = read();
    i64 Start_Time_Without_Read = clock();
    if (a == 1 && b == 1 && c == 1)
      return fprintf(fout, "%lld\n", h), void();
    for (i32 i = 0; i < c; ++i) {
      e[i].eb((i + a) % c, a);
      e[i].eb((i + b) % c, b);
    }
    spfa();
    i64 ans = 0;
    for (i32 i = 0; i < c; ++i) if (dis[i] <= h) ans += (h - dis[i]) / c + 1;
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P3403::main(), 0; }
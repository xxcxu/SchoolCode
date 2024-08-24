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
namespace Solution_Of_BZOJ4152 {
  bool _1;
  static constexpr i32 N = 200005;
  i32 n;
  i64 dis[N];
  bool vis[N];
  std::tuple<i32, i32, i32> a[N], b[N], c[N];
  std::vector<std::pair<i32, i32>> e[N];
  bool _2;
  struct Node {
    i32 x, dis;
    Node(i32 x = 0, i32 dis = 0): x(x), dis(dis) {}
    const bool operator <(const Node &a) const { return this->dis > a.dis; }
  };
  void dijkstra() {
    std::priority_queue<Node> q;
    std::memset(dis, 0x3f, sizeof dis);
    std::memset(vis, 0, sizeof vis);
    q.ep(1, dis[1] = 0);
    while (q.size()) {
      i32 x = q.top().x; q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto &[y, z] : e[x])
        if (dis[y] > dis[x] + z)
          q.ep(y, dis[y] = dis[x] + z);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      auto &[x, y, id] = a[i];
      x = read(), y = read(), id = i;
    }
    for (i32 i = 1; i <= n; ++i) b[i] = c[i] = a[i];
    std::sort(b + 1, b + n + 1, [&](std::tuple<i32, i32, i32> x, std::tuple<i32, i32, i32> y) { return std::get<0>(x) < std::get<0>(y); });
    std::sort(c + 1, c + n + 1, [&](std::tuple<i32, i32, i32> x, std::tuple<i32, i32, i32> y) { return std::get<1>(x) < std::get<1>(y); });
    for (i32 i = 1; i < n; ++i) {
      auto &[x, y, id] = b[i];
      auto &[xx, yy, ID] = b[i + 1];
      e[id].eb(ID, xx - x);
      e[ID].eb(id, xx - x);
    }
    for (i32 i = 1; i < n; ++i) {
      auto &[x, y, id] = c[i];
      auto &[xx, yy, ID] = c[i + 1];
      e[id].eb(ID, yy - y);
      e[ID].eb(id, yy - y);
    }
    dijkstra();
    fprintf(fout, "%lld\n", dis[n]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_BZOJ4152::main(), 0; }
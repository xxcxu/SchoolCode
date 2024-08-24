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
namespace Solution_Of_P6822 {
  bool _1;
  static const i32 N = 200005;
  i32 n, m, s;
  i32 val[N * 2];
  i64 dis[N * 2];
  bool vis[N * 2];
  struct Node {
    i32 to, link, id;
    Node() = default;
    Node(i32 to, i32 link, i32 id = 0): to(to), link(link), id(id) {}
    bool operator <(const Node &a) const { return this->link < a.link; }
  };
  struct node {
    i32 x; i64 dis;
    node(i32 x = 0, i64 dis = 0): x(x), dis(dis) {}
    const bool operator <(const node &a) const { return this->dis > a.dis; }
  };
  std::vector<i32> g[N * 2];
  std::vector<Node> e[N * 2];
  bool _2;
  void dijkstra(i32 s) {
    std::priority_queue<node> q;
    std::memset(dis, 0x3f, sizeof dis);
    std::memset(vis, 0, sizeof vis);
    q.ep(s, dis[s] = 0);
    while (q.size()) {
      i32 x = q.top().x; q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto &[y, z, id] : e[x]) {
        if (dis[y] > dis[x] + z) {
          q.ep(y, dis[y] = dis[x] + z);
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
    for (i32 i = 1; i <= m; ++i) {
      static i32 x, y, z;
      x = read(), y = read(), z = read();
      g[x].eb(i), g[y].eb(i + m);
      val[i + m] = val[i] = z;
    }
    for (i32 i = 1; i <= m; ++i)
      e[i].eb(i + m, val[i]), e[i + m].eb(i, val[i]);
    i32 s = m * 2 + 1;
    for (auto i : g[1]) e[s].eb(i, val[i]);
    for (i32 i = 2; i < n; ++i) {
      std::sort(all(g[i]), [&](const i32 &a, const i32 &b) { return val[a] < val[b]; });
      i32 m = g[i].size();
      for (i32 j = 0; j < m - 1; ++j) {
        i32 x = g[i][j], y = g[i][j + 1];
        e[x].eb(y, val[y] - val[x]);
        e[y].eb(x, 0);
      }
    }
    dijkstra(s);
    i64 ans = INT64_MAX;
    for (auto p : g[n]) chkmin(ans, dis[p]);
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P6822::main(), 0; }
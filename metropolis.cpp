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
constexpr bool chkmax(T1 &a, T2 b) { return a < b ? (a = b, true) : false; } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_metropolis {
  bool _1;
  static const i32 N = 1000005;
  i32 n, m;
  i32 dis1[N]; i64 dis2[N];
  bool vis[N];
  using Edge = std::pair<i32, i32>;
  std::vector<Edge> e[N];
  bool _2;
  struct Node {
    i32 x, w1, w2;
    Node() = default;
    Node(i32 _x, i32 _w1, i32 _w2):
      x(_x), w1(_w1), w2(_w2) {}
    bool operator <(const Node &other) const {
      if (this->w1 != other.w1) return this->w1 > other.w1;
      return this->w2 < other.w2;
    }
  };
  void dijkstra(i32 s) {
    std::memset(dis1, 0x3f, sizeof dis1);
    std::memset(dis2, 128, sizeof dis2);
    std::memset(vis, 0, sizeof vis);
    std::priority_queue<Node> q;
    q.ep(s, dis1[s] = 0, dis2[s] = 0LL);
    while (q.size()) {
      i32 x = q.top().x; q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto &[y, z] : e[x])
        if (chkmin(dis1[y], dis1[x] + z) || (dis1[y] == dis1[x] + z && chkmax(dis2[y], dis2[x] + z * z)))
          dis2[y] = dis2[x] + z * z, q.ep(y, dis1[y], dis2[y]);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("metropolis.in", "r");
    fout = fopen("metropolis.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 s, lst, now, w;
      s = read();
      for (i32 j = 1; j <= 2 * s + 1; ++j) {
        i32 t = read();
        if (j & 1) now = t; else w = t;
        if (j > 1 && (j & 1)) e[lst].eb(now, w);
        if (j & 1) lst = now;
      }
    }
    dijkstra(1);
    fprintf(fout, "%d %lld\n", dis1[n], dis2[n]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_metropolis::main(), 0; }
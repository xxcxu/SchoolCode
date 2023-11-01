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
constexpr bool chkmax(T1 &a, T2 b) { return a >= b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a <= b ? false : (a = b, true); } 
#pragma endregion
namespace Solution_Of_HLP1461 {
  bool _1;
  static const i32 N = 505;
  static const i64 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 n, k;
  i32 a[N][8], b[N][8];
  i64 dis[N * 8][1 << 8];
  std::vector<std::pair<i32, i32>> e[N * 8];
  bool vis[N * 8][1 << 8];
  bool _2;
  i32 id(i32 x, i32 k) { return k * n + x; }
  struct Node {
    i32 x; i64 d; i32 S;
    Node() = default;
    Node(i32 x, i64 d, i32 S): x(x), d(d), S(S) {}
    bool operator <(const Node &other) const { return this->d > other.d; }
  };
  i32 get(i32 x) { return (x - 1) / n; }
  i64 dijkstra() {
    std::priority_queue<Node> q;
    std::memset(dis, 0x3f, sizeof dis);
    std::memset(vis, 0, sizeof vis);
    for (i32 i = 0; i < k; ++i) q.ep(id(1, i), dis[id(1, i)][1 << i] = a[1][i], 1 << i);
    while (q.size()) {
      i32 u = q.top().x;
      i32 S = q.top().S;
      q.pop();
      if (vis[u][S]) continue;
      vis[u][S] = true;
      for (auto &[v, w] : e[u])
        if (~S >> get(v) & 1) {
          if (chkmin(dis[v][S | (1 << get(v))], dis[u][S] + w))
            q.ep(v, dis[v][S | (1 << get(v))], S | (1 << get(v)));
        } else {
          if (get(v) == get(u))
            if (chkmin(dis[v][S], dis[u][S] + w))
              q.ep(v, dis[v][S], S);
        }
    }
    i64 ans = inf64;
    for (i32 S = 0; S < (1 << 8); ++S)
      for (i32 i = 0; i < 8; ++i)
        if (S >> i & 1)
          chkmin(ans, dis[id(n, i)][S] + b[n][i]);
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("subway.in", "r");
    fout = fopen("subway.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 0; i < k; ++i) {
      for (i32 j = 1; j <= n; ++j) a[j][i] = read();
      for (i32 j = 1; j <= n; ++j) b[j][i] = read();
      i32 m = read();
      for (i32 j = 1; j <= m; ++j) {
        static i32 u, v, w;
        u = read(), v = read(), w = read();
        e[id(u, i)].eb(id(v, i), w);
        e[id(v, i)].eb(id(u, i), w);
      }
    }
    for (i32 i = 0; i < k; ++i)
      for (i32 j = 0; j < k; ++j)
        if (i != j)
          for (i32 p = 1; p <= n; ++p)
            e[id(p, i)].eb(id(p, j), b[p][i] + a[p][j]);
    fprintf(fout, "%lld\n", dijkstra());
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1461::main(), 0; }
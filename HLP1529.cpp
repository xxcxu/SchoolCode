// 郑梓妍😭 钟晨瑶😭
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
namespace Solution_Of_HLP1529 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, q;
  i32 cnt, a[N], b[N], head[N];
  struct Node {
    i32 to, s, t;
    Node() = default;
    Node(i32 _to, i32 _s, i32 _t):
      to(_to), s(_s), t(_t) {}
  };
  std::vector<Node> e[N];
  i32 dist[N];
  bool vis[N];
  bool _2;
  i32 solve(i32 et) {
    std::priority_queue<std::pair<i32, i32>> q;
    std::vector<i32> vec;
    q.ep(dist[n] = et, n);
    while (q.size()) {
      i32 x = q.top().second; q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      vec.eb(x);
      for (i32 &i = head[x]; i < (i32)e[x].size(); ++i) {
        auto& [y, s, t] = e[x][i];
        if (dist[x] >= t) {
          if (chkmax(dist[y], s))
            q.ep(dist[y], y);
        } else break;
      }
    }
    for (i32 i : vec) vis[i] = false;
    return dist[1];
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tp.in", "r");
    fout = fopen("tp.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, x, y;
      u = read(), v = read(), x = read(), y = read();
      e[v].eb(u, x, y);
    }
    for (i32 i = 1; i <= n; ++i)
      std::sort(all(e[i]), [&](const Node &a, const Node &b) { return a.t < b.t; });
    std::memset(dist, 128, sizeof dist);
    a[++cnt] = dist[1];
    b[cnt] = 0;
    for (auto it : e[n]) {
      a[++cnt] = solve(it.t);
      b[cnt] = it.t;
    }
    b[++cnt] = 90000001;
    q = read();
    while (q--) {
      static i32 et;
      et = read();
      i32 p = std::upper_bound(b + 1, b + cnt + 1, et) - b - 1;
      fprintf(fout, "%d\n", a[p] == dist[0] ? -1 : a[p]);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1529::main(), 0; }
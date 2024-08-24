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
namespace Solution_Of_C24062 {
  bool _1;
  static const i32 N = 200005, M = 511;
  i32 n, m;
  i32 val[N], dis[N];
  std::set<std::pair<i32, i32>> s[512];
  std::vector<i32> e[N];
  bool _2;
  void erase(i32 x) {
    s[val[x] & M].erase(std::pair<i32, i32>(val[x], x));
    return void();
  }
  void bfs() {
    std::queue<i32> q;
    q.ep(1);
    dis[1] = 0;
    erase(1);
    while (q.size()) {
      i32 x = q.front(); q.pop();
      for (i32 y : e[x]) {
        if (dis[y] >= 0) continue;
        erase(y);
        dis[y] = dis[x] + 1;
        q.ep(y);
      }
      std::vector<i32> vec;
      for (i32 i = 8; i >= 0; --i)
        if ((val[x] & M) >> i & 1) vec.eb(i);
      i32 k = (i32)vec.size();
      for (i32 i = 0; i < (1 << k); ++i) {
        i32 v = 0;
        for (i32 j = 0; j < k; ++j) if (i >> j & 1) v ^= (1 << vec[j]);
        std::vector<i32> t;
        for (auto it = s[v].begin(); it != s[v].end(); ++it) {
          if (it->first > val[x]) break;
          if (((it->first) & val[x]) == (it->first)) {
            if (dis[it->second] >= 0) continue;
            t.eb(it->second);
            dis[it->second] = dis[x] + 1;
            q.ep(it->second);
          }
        }
        for (auto it : t) erase(it);
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("walk.in", "r");
    fout = fopen("walk.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    std::memset(dis, -1, sizeof dis);
    for (i32 i = 1; i <= n; ++i) val[i] = read();
    for (i32 i = 1; i <= n; ++i) s[val[i] & M].insert(std::pair<i32, i32>(val[i], i));
    for (i32 i = 1; i <= m; ++i) {
      i32 u, v;
      u = read(), v = read();
      e[u].eb(v);
    }
    bfs();
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", dis[i]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_C24062::main(), 0; }
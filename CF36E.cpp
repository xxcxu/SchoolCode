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
namespace Solution_Of_CF36E {
  bool _1;
  static constexpr i32 N = 10005;
  i32 n, m;
  i32 deg[N];
  std::multiset<i32> s[N];
  std::vector<std::pair<i32, i32>> path;
  bool _2;
  void Euler(i32 x) {
    for (auto y : s[x]) if (s[x].find(y) != s[x].end()) {
      s[x].erase(s[x].find(y));
      s[y].erase(s[y].find(x));
      --deg[x], --deg[y];
      path.eb(x, y);
      Euler(y);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = N - 5, m = read();
    i32 p1, p2;
    for (i32 i = 1; i <= m; ++i) {
      static i32 x, y;
      x = read(), y = read();
      s[x].ep(y), s[y].ep(x);
      ++deg[x], ++deg[y];
      p1 = x, p2 = y;
    }
    i32 cnt = 0, p[4] = {};
    for (i32 i = 1; i <= n; ++i) if (deg[i] & 1) p[cnt++] = i;
    if (cnt) p1 = p[0], p2 = p[1];
    ++deg[p1], ++deg[p2], s[p1].ep(p2), s[p2].ep(p1);
    Euler(p1);
    i32 l;
    for (auto [x, y] : path) fprintf(fout, "%d %d\n", x, y);
    // for (i32 i = 0; i < path.size(); ++i) if (auto &[x, y] = path[i]; x == p1 && y == p2) { l = i; break; }
    // for (i32 i = 0; i < path.size(); ++i) if (auto &[x, y] = path[i]; x == p2 && y == p1) { l = i; break; }
    // fprintf(fout, "%d\n", l);
    // for (i32 i = 0; i < l; ++i) fprintf(fout, "%d %d\n", path[i].first, path[i].second);
    // fprintf(fout, "%d\n", (i32)path.size() - l - 1);
    // for (i32 i = l + 1; i < path.size(); ++i) fprintf(fout, "%d %d\n", path[i].first, path[i].second);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF36E::main(), 0; }
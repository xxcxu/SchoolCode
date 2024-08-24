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
namespace Solution_Of_HLP1615 {
  bool _1;
  i64 n;
  std::map<i64, i32> map;
  bool _2;
  i32 dfs(i64 x) {
    if (x == 0) return 0;
    if (map.find(x) != map.end()) return map[x];
    for (i32 i = 1; i <= 5; ++i)
      for (i32 j = i; j <= 3 * i; ++j)
        if ((x - j) % 10 == 0 && dfs((x - j) / 10) <= i) return map[x] = i;
  }
  void solve() {
    n = read();
    fprintf(fout, "%d\n", dfs(n));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("philo.in", "r");
    fout = fopen("philo.out", "w");
    i32 t = read();
    while (t--) solve();
    return void();
  }
}
signed main() { return Solution_Of_HLP1615::main(), 0; }
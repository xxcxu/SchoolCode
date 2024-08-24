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
namespace Solution_Of_ {
  bool _1;
  static const i32 N = 1005;
  i32 n, ans;
  i32 a[N][N];
  i32 r[N], c[N];
  i32 ansr[N * N], ansc[N * N];
  bool _2;
  std::vector<std::pair<i32, i32>> v[N * N];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fin = fopen("minimax.in", "r");
    fout = fopen("minimax.out", "w");
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        a[i][j] = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        v[a[i][j]].eb(i, j);
    ans = n * n;
    for (i32 i = 1; i <= n; ++i) r[i] = n;
    for (i32 i = 1; i <= n; ++i) c[i] = n;
    ansr[1000000 + 1] = n; 
    ansc[0] = n; 
    for (i32 i = 1000000; i >= 1; --i) {
      ansr[i] = ansr[i + 1];
      for (auto &[x, y] : v[i]) --r[x], chkmin(ansr[i], r[x]);
    }
    for (i32 i = 1; i <= 1000000; ++i) {
      ansc[i] = ansc[i - 1];
      for (auto &[x, y] : v[i]) --c[y], chkmin(ansc[i], c[y]);
    }
    for (i32 i = 1; i <= 1000000; ++i) ans = std::min(ans, ansr[i] + ansc[i]);
    fprintf(fout, "%d\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }

// 1 1 1 1
// 9 14 15 8
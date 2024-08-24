#pragma region
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
#pragma endregion
namespace Solution_Of_CF741C {
  bool _1;
  static const i32 N = 200005;
  i32 n, u[N], v[N], col[N];
  bool flag = false;
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 c) {
    if (col[x] && col[x] != c) flag = true;
    if (col[x]) return void();
    col[x] = c;
    for (i32 y : e[x]) dfs(y, 3 - c);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      u[i] = read(), v[i] = read();
      e[u[i]].eb(v[i]), e[v[i]].eb(u[i]);
    }
    for (i32 i = 1; i <= n; ++i) {
      e[i * 2 - 1].eb(i * 2);
      e[i * 2].eb(i * 2 - 1);
    }
    for (i32 i = 1; i <= n * 2; ++i)
      if (!col[i]) dfs(i, 1);
    if (flag) return fputs("-1", fout), void();
    for (i32 i = 1; i <= n; ++i)
      fprintf(fout, "%d %d\n", col[u[i]], col[v[i]]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF741C::main(), 0; }
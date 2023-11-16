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
namespace Solution_Of_HLP1516 {
  bool _1;
  static const i32 N = 20;
  i32 n, m, ans;
  i32 a[N], f[1 << N];
  i64 b[N];
  bool _2;
  void work(i32 S) {
    if (f[S] == 1) {
      i32 lst = 0;
      for (i32 i = 0; i < n; ++i)
        if (S >> i & 1) {
          if (!lst) { lst = i + 1; continue;}
          if (b[lst]) fprintf(fout, "%d %d %lld\n", lst, i, b[lst]);
          b[i + 1] += b[lst];
          b[lst] = 0;
          lst = i + 1;
        }
      return void();
    }
    for (i32 T = S & (S - 1); T; T = (T - 1) & S)
      if (f[S] == f[T] + f[S ^ T]) {
        work(T); work(S ^ T);
        return void();
      }
    return void();
  }
  void solve() {
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(); a[++n] = 0;
    for (i32 i = 1; i <= n; ++i) b[i] = a[i] - a[i - 1];
    std::vector<i32> vec;
    i32 R = (1 << n) - 1;
    for (i32 S = 1; S <= R; ++S) {
      f[S] = -1e9;
      i64 sum = 0;
      bool flag = true;
      for (i32 i = 0; i < n; ++i)
        if (S >> i & 1) {
          sum += b[i + 1];
          if (sum < 0) flag = false;
        }
      if (flag && sum == 0) vec.eb(S), f[S] = 1;
    }
    for (auto S : vec) {
      i32 mask = S ^ R;
      if (f[S] != 1) continue;
      for (i32 T = mask; T; T = (T - 1) & mask)
        if (f[T] > 0) chkmax(f[S | T], f[S] + f[T]);
    }
    fprintf(fout, "%d\n", n - f[R]);
    work(R);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("build.in", "r");
    fout = fopen("build.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read(); 
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1516::main(), 0; }
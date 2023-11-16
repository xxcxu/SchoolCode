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
namespace Solution_Of_FZSDF160_2 {
  bool _1;
  static const i32 N = 200005;
  i32 n, B;
  i32 a[N], b[N];
  i64 dp[5005][5005];
  bool _2;
  void solve() {
    n = read(), B = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), b[i] = read();
    a[n + 1] = 0;
    i64 ans = a[1], sum = 0, now = 0, skip = 0;
    std::priority_queue<i32> q;
    for (i32 i = 1; i <= n; ++i) {
      sum += a[i];
      now += a[i] - b[i];
      q.ep(b[i]);
      while (q.size() && q.top() > B && now < 0) {
        now += q.top() - B;
        q.pop();
        ++skip;
      }
      if (now >= 0) chkmax(ans, sum + a[i + 1] - B * skip);
      else break;
    }
    fprintf(fout, "%lld\n", ans);
    return void();  
  }   
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("piece.in", "r");
    fout = fopen("piece.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read();
    while (t--) solve();h
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF160_2::main(), 0; }
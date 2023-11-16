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
namespace Solution_Of_HLP1550 {
  bool _1;
  static const i32 N = 1005;
  i32 n, a[N];
  i64 s, ans;
  i32 prime[100005], cnt;
  bool vis[100005];
  std::vector<i32> factor;
  bool _2;
  void init(i32 n) {
    cnt = 0;
    for (i32 i = 2; i <= n; ++i) {
      if (!vis[i]) prime[++cnt] = i;
      for (i32 j = 1; i * prime[j] <= n; ++j) {
        vis[i * prime[j]] = true;
        if (i % prime[j] == 0) break;
      }
    }
    return void();
  }
  i64 solve(i32 p) {
    i64 res = s;
    for (i32 i = 1; i <= n; ++i)
      if (a[i] % p != 0)
        res -= a[i];
    return res;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("divisor.in", "r");
    fout = fopen("divisor.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    init(100005);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), s += a[i];
    for (i32 i = 1; i <= n; ++i) {
      i32 p = a[i];
      for (i32 j = 1; j <= cnt && prime[j] <= p; ++j) {
        if (p % prime[j] == 0) factor.eb(prime[j]);
        while (p % prime[j] == 0) p /= prime[j];
      }
      if (p != 1) factor.eb(p);
    }
    std::sort(all(factor));
    factor.erase(std::unique(all(factor)), factor.end());
    for (i32 i : factor) ans = std::max(ans, solve(i));
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1550::main(), 0; }
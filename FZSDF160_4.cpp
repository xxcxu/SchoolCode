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
namespace Solution_Of_FZSDF160_4 {
  bool _1;
  static const i32 N = 200005, M = N * 5;
  static const i32 P = 1000000007;
  i32 n, ans;
  i32 a[N], b[N], c[N];
  std::vector<i32> factor;
  bool vis[M];
  i32 cnt, prime[N], mp[M];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  void init(i32 n) {
    for (i32 i = 2; i <= n; ++i) {
      if (!vis[i]) prime[++cnt] = i, mp[i] = i;
      for (i32 j = 1; i * prime[j] <= n; ++j) {
        vis[i * prime[j]] = true;
        mp[i * prime[j]] = prime[j];
        if (i % prime[j] == 0) break;
      }
    }
    return void();
  }
  i32 calc(i32 l, i32 r) {
    for (i32 i = 1; i <= (r - l + 1); ++i)
      c[i] = b[i + l - 1];
    std::sort(c + 1, c + (r - l + 1) + 1);
    return c[((r - l + 1) + 1) >> 1];
  }
  void work(i32 p) {
    for (i32 i = 1; i <= n; ++i) {
      b[i] = 0;
      i32 q = a[i];
      while (q % p == 0) q /= p, ++b[i];
    }
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = i; j <= n; ++j) {
        i32 mid = calc(i, j);
        i32 s = 0;
        for (i32 k = i; k <= j; ++k) s = inc(s, std::abs(b[k] - mid));
        ans = inc(ans, s);
      }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("unnamed.in", "r");
    // fout = fopen("unnamed.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    init(1000000);
    for (i32 i = 1; i <= n; ++i) {
      i32 p = a[i];
      for (i32 j = 1; (j <= cnt) && prime[j] <= p; ++j)
        if (p % prime[j] == 0) {
          while (p % prime[j] == 0) p /= prime[j];
          factor.eb(prime[j]);
        }
    }
    std::sort(all(factor));
    factor.erase(std::unique(all(factor)), factor.end());
    for (i32 i : factor) work(i);
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_FZSDF160_4::main(), 0; }
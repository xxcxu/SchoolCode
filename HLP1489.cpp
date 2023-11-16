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
namespace Solution_Of_HLP1489 {
  bool _1;
  static const i32 N = 500005;
  static const i64 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 n, m, q;
  i32 a[N], b[N], c[N];
  i64 sum[N];
  i64 f[N][20];
  bool _2;
  void init() {
    for (i32 i = 1; i <= n; ++i) f[i][0] = a[i] - sum[i];
    for (i32 j = 1; j <= 19; ++j)
      for (i32 i = 1; i + (1 << j) - 1 <= n; ++i)
        f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    return void();
  }
  i64 query(i32 l, i32 r) {
    if (l > r) return inf64;
    i32 k = std::log2(r - l + 1);
    return std::min(f[l][k], f[r - (1 << k) + 1][k]);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr; 
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) b[i] = read();
    for (i32 i = 1; i <= n; ++i) c[i] = read();
    for (i32 i = 1; i <= n; ++i) sum[i] = sum[i - 1] + b[i];
    q = read(); 
    init();
    while (q--) {
      m = read();
      std::vector<i32> vec;
      vec.resize(m + 2);
      i64 sb = 0;
      for (i32 i = 1; i <= m; ++i) vec[i] = read();
      for (i32 i = 1; i <= m; ++i) sb += b[vec[i]];
      i64 now = 0;
      i64 ans = sum[n] - sb;
      vec[m + 1] = n + 1;
      ans = std::min(ans, sum[n] - sb + query(1, m ? vec[1] - 1 : n));
      for (i32 i = 1; i <= m; ++i) {
        now += c[vec[i]] + b[vec[i]];
        ans = std::min(ans, query(vec[i], vec[i + 1] - 1) + now - sb + sum[n]);
      }
      fprintf(fout, "%lld\n", ans);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1489::main(), 0; }  
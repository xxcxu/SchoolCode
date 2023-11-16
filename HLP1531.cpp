// 郑梓妍😭 钟晨瑶😭
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
namespace Solution_Of_HLP1531 {
  bool _1;
  static const i32 N = 5005;
  static const i32 P = 1000000007;
  i32 n, Case;
  i32 f[N], dp[N][3];
  char s[N], t[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("zvezda.in", "r");
    fout = fopen("zvezda.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();  
    Case = read(); n = read();
    fscanf(fin, "%s %s", s + 1, t + 1);
    for (i32 i = 1; i <= n; ++i) s[i] -= '0', t[i] -= '0';
    if (Case == 1) {
      for (i32 i = 1; i <= n; ++i) {
        if (t[i] == 1) {
          f[i] = f[i - 1];
        } else {
          if (s[i] == 0) f[i] = mul(f[i - 1], 2);
          else f[i] = inc(mul(f[i - 1], 2), 1);
        }
      }
      fprintf(fout, "%d\n", f[n]);
    }
    if (Case == 2) {  
      for (i32 i = 0; i < n; ++i) {
        for (i32 j = 0; j < 3; ++j)
          for (i32 k = 0; k < 2; ++k) {
            i32 now = (j + (((n - i) & 1) ? 1 : 2) * (((s[i + 1] ^ k) & t[i + 1]))) % 3;
            dp[i + 1][now] = inc(dp[i + 1][now], dp[i][j]);
          }
        for (i32 j = 0; j < s[i + 1]; ++j) {
          i32 now = (((n - i) & 1) ? 1 : 2) * ((s[i + 1] ^ j) & t[i + 1]) % 3;
          dp[i + 1][now] = inc(dp[i + 1][now], 1);
        }
      }
      fprintf(fout, "%d\n", dp[n][0]); 
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1531::main(), 0; }
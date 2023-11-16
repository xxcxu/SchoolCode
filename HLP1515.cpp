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
namespace Solution_Of_HLP1515 {
  bool _1;
  static const i32 P = 1000000007;
  i32 n = 136;
  i32 f[150][14][2];
  char s[10];
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  } 
  i32 inv(i32 x) { return qpow(x, P - 2); }
  void solve() {
    bool _1m = false, _1s = false, _1p = false;
    bool _9m = false, _9s = false, _9p = false;
    bool _E = false, _S = false, _W = false, _N = false;
    bool _M = false, _F = false, _B = false;
    i32 cnt = 0, cnt2 = 0;
    for (i32 i = 1; i <= 13; ++i) {
      fscanf(fin, "%s", s);
      if (s[0] == '1') {
        if (s[1] == 'm') { cnt += !_9m; _9m = true; }
        if (s[1] == 's') { cnt += !_9s; _9s = true; }
        if (s[1] == 'p') { cnt += !_9p; _9p = true;}
        ++cnt2;
      }
      if (s[0] == '9') {
        if (s[1] == 'm') { cnt += !_1m; _1m = true; }
        if (s[1] == 's') { cnt += !_1s; _1s = true; }
        if (s[1] == 'p') { cnt += !_1p; _1p = true; }
        ++cnt2;
      }
      if (s[0] == 'E') { cnt += !_E; _E = true; ++cnt2; }
      if (s[0] == 'S') { cnt += !_S; _S = true; ++cnt2; }
      if (s[0] == 'W') { cnt += !_W; _W = true; ++cnt2; }
      if (s[0] == 'N') { cnt += !_N; _N = true; ++cnt2; }
      if (s[0] == 'M') { cnt += !_M; _M = true; ++cnt2; }
      if (s[0] == 'F') { cnt += !_F; _F = true; ++cnt2; }
      if (s[0] == 'B') { cnt += !_B; _B = true; ++cnt2; }
    }
    fprintf(fout, "%d\n", f[n - 13][cnt][cnt != cnt2]);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mahjong.in", "r");
    fout = fopen("mahjong.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j = 0; j <= 13; ++j) {
        f[i][j][0] = inc(mul(inc(mul(4, 13 - j, f[i - 1][j + 1][0]), mul(3, j, f[i - 1][j][1]), mul(i - 4 * 13 + j, f[i - 1][j][0])), inv(i)), 1);
        f[i][j][1] = inc(mul(inc(mul(4, 13 - j, f[i - 1][j + 1][1]), mul((i - 4 * (13 - j)), f[i - 1][j][1])), inv(i)), 1);
      }
      f[i][13][1] = 0;
    }
    i32 t = read();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1515::main(), 0; }
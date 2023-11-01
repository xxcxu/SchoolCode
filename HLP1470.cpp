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
namespace Solution_Of_HLP1470 {
  bool _1;
  static const i32 N = 25;
  static const i32 mod = 1000000007;
  static const i32 inv1000000 = 142857001;
  i32 n, m, ans;
  i32 p[4][N][N], sp0[N][1 << 10], dp[N][1 << 10][N][35];
  i32 point[N], cnt[1 << 10];
  i32 lp[N][1 << 10][35], relp[N][1 << 10][35];
  i32 lsp[N][1 << 10][35], psl[N][1 << 10][35];
  bool _2;
#pragma region
  i32 inc(i32 x, i32 y) { return (x + y) % mod; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + mod - y) % mod; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % mod; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  void plus(i32 &x, i32 y) { return x = inc(x, y), void(); }
  template<typename ...Args>
  void plus(i32 &x, Args ...args) { return x = inc(x, args...), void(); }
  void cmul(i32 &x, i32 y) { return x = mul(x, y), void(); }
  template<typename ...Args>
  void cmul(i32 &x, Args ...args) { return x = mul(x, args...), void(); }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, cmul(x, x))
      if (y & 1) cmul(ans, x);
    return ans;
  }
#pragma endregion
  void dfs(i32 pos, i32 x, i32 P, i32 S, i32 mask) {
    if (x == m + 1) {
      plus(lp[pos][mask][S], P);
      return void();
    }
    if (mask >> (x - 1) & 1) {
      dfs(pos, x + 1, mul(P, p[0][x][pos]), S, mask);
    } else {
      for (i32 i = 0; i <= 3; ++i)
        point[x] = i, dfs(pos, x + 1, mul(P, p[i][x][pos]), S + i, mask);
    }
    return void();
  }
  i32 count(i32 x) { 
    i32 res = 0;
    while (x) {
      ++res;
      x -= x & -x;
    }
    return res;
  }
  std::map<std::tuple<i32, i32, i32>, i32> map;
  void dfs2(i32 pos, i32 x, i32 P, i32 sum, i32 mask) {
    if (x == m + 1) {
      if (!sum) return void();
      i32 T = ((1 << m) - 1) ^ mask;
      i32 pp = dp[pos][mask][m][sum];
      // i32 pp = 1;
      // if (map.find(std::make_tuple(pos, sum, mask)) != map.end()) pp = map[std::make_tuple(pos, sum, mask)];
      // else {
      //   for (i32 S = T; S; S = (S - 1) & T) {
      //     i32 Q = mul(lsp[pos + 1][mask | S][sum], psl[pos - 1][mask | S][sum]);  
      //     if (cnt[S] & 1) pp = dec(pp, Q);  
      //     else pp = inc(pp, Q);
      //   }
      //   map[std::make_tuple(pos, sum, mask)] = pp;
      // }
      P = mul(P, pp);
      ans = inc(ans, mul(P, sum));
      return void();
    }
    for (i32 i = 0; i <= 3; ++i)
      dfs2(pos, x + 1, mul(P, p[i][x][pos]), sum + i, mask | ((1 << (x - 1)) * (i != 0)));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 point = 1; point <= 3; ++point) {
      for (i32 i = 1; i <= m; ++i)
        for (i32 j = 1; j <= n; ++j)
          p[point][i][j] = mul(read(), inv1000000);
    }
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= m; ++i)
      for (i32 j = 1; j <= n; ++j)
        p[0][i][j] = dec(1, inc(p[1][i][j], p[2][i][j], p[3][i][j]));
    cnt[0] = 0;
    for (i32 S = 1; S < (1 << m); ++S) cnt[S] = cnt[S ^ (S & -S)] + 1;
    for (i32 S = 0; S < (1 << m); ++S)
      for (i32 j = 1; j <= 30; ++j) psl[0][S][j] = 1, lsp[n + 1][S][j] = 1;
    for (i32 S = 0; S < (1 << m); ++S)
      for (i32 i = 1; i <= m; ++i) {
        sp0[i][S] = 1;
        for (i32 j = 1; j <= n; ++j) {
          sp0[i][S] = mul(sp0[i][S], p[0][i][j]);
        }
      }
    for (i32 pos = 1; pos <= n; ++pos)
      for (i32 S = 0; S < (1 << m); ++S) {
        dp[pos][S][0][0] = 1;
        for (i32 i = 1; i <= m; ++i) {
          if (S >> (i - 1) & 1) {
            for (i32 j = 0; j <= 30; ++j) {
              dp[pos][S][i][j] = mul(dp[pos][S][i - 1][j], sp0[i][S], qpow(p[0][i][pos], mod - 2));
            }
          }
          else {
            for (i32 j = 1; j <= n; ++j) {
              if (j != pos) {
                for (i32 k = 0; k <= 30; ++k) {
                  if (k - 1 >= 0) plus(dp[pos][S][i][k], mul(dp[pos][S][i - 1][k - 1], p[1][i][j], sp0[i][S], qpow(p[0][i][pos], mod - 2), qpow(p[0][i][j], mod - 2)));
                  if (k - 2 >= 0) plus(dp[pos][S][i][k], mul(dp[pos][S][i - 1][k - 2], p[2][i][j], sp0[i][S], qpow(p[0][i][pos], mod - 2), qpow(p[0][i][j], mod - 2)));
                  if (k - 3 >= 0) plus(dp[pos][S][i][k], mul(dp[pos][S][i - 1][k - 3], p[3][i][j], sp0[i][S], qpow(p[0][i][pos], mod - 2), qpow(p[0][i][j], mod - 2)));
                }
              }
            }
          }
        }
        for (i32 j = 1; j <= 30; ++j)
          plus(dp[pos][S][m][j], dp[pos][S][m][j - 1]);
      }
    for (i32 i = 1; i <= n; ++i) 
      for (i32 S = 0; S < (1 << m); ++S) {
        dfs(i, 1, 1, 0, S);
        for (i32 j = 1; j <= 30; ++j) plus(lp[i][S][j], lp[i][S][j - 1]);
        for (i32 j = 1; j <= 30; ++j) psl[i][S][j] = mul(psl[i - 1][S][j], lp[i][S][j - 1]);
      }
    for (i32 i = n; i >= 1; --i)
      for (i32 S = 0; S < (1 << m); ++S)
        for (i32 j = 1; j <= 30; ++j) lsp[i][S][j] = mul(lsp[i + 1][S][j], lp[i][S][j]);
    for (i32 i = 1; i <= n; ++i) dfs2(i, 1, 1, 0, 0); 
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1470::main(), 0; }
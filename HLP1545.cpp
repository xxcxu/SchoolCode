#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
inline constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
inline constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_HLP1545 {
  bool _1;
  static const i32 N = 403;
  static const i64 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 n, L, R;
  i32 a[N], sum[N];
  i64 dp[N][N], g[N][N];
  bool _2;
  void solve() {
    n = read(), L = read(), R = read();
    if ((R == 1 && n != 1) || (L > R)) return fputs("-1\n", fout), void();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    std::memset(g, 0x3f, sizeof g);
    for (i32 i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    for (i32 i = 1; i <= n; ++i) g[i][i] = 0;
    for (i32 l = n; l >= 1; --l) {
      std::memset(dp, 0x3f, sizeof dp);
      dp[l - 1][0] = 0;
      for (i32 r = l; r <= n; ++r) {
        for (i32 i = 1; i <= r - l + 1 && i <= R; ++i)
          for (i32 p = l; p <= r; ++p)
            dp[r][i] = dp[r][i] < dp[p - 1][i - 1] + g[p][r] ? dp[r][i] : dp[p - 1][i - 1] + g[p][r];
        for (i32 i = L; i <= R; ++i)
          g[l][r] = g[l][r] < dp[r][i] + sum[r] - sum[l - 1] ? g[l][r] : dp[r][i] + sum[r] - sum[l - 1];
        dp[r][1] = dp[r][1] < g[l][r] ? dp[r][1] : g[l][r];
      }
    }
    fprintf(fout, "%lld\n", g[1][n] == inf64 ? -1 : g[1][n]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("rock.in", "r");
    fout = fopen("rock.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = 1;
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1545::main(), 0; }
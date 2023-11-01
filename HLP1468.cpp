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
namespace Solution_Of_HLP1468 {
  bool _1;
  static const i32 N = 200005;
  static const i32 P = 998244353;
  i32 n;
  i32 a[N], dp[N];
  char s[N];
  i32 head[27], tail[27], lst[27];
  i32 pre[N], nxt[N], to[N][27];
  bool isend[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void solve() {
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    for (i32 i = 1; i <= n; ++i) a[i] = s[i] - 'a' + 1;
    std::fill(head + 1, head + 26 + 1, n + 1);
    std::fill(tail + 1, tail + 26 + 1, 0);
    std::memset(lst, 0, sizeof lst);
    std::memset(isend, 0, (n + 1) * sizeof(bool));
    std::fill(pre + 1, pre + n + 1, 0);
    std::fill(nxt + 1, nxt + n + 1, n + 1);
    std::memset(dp, 0, (n + 1) * sizeof(i32));
    for (i32 i = 1; i <= n; ++i) pre[i] = lst[a[i]], nxt[lst[a[i]]] = i, lst[a[i]] = i;
    for (i32 i = 1; i <= n; ++i) chkmin(head[a[i]], i);
    for (i32 i = 1; i <= n; ++i) chkmax(tail[a[i]], i);
    for (i32 i = 1; i <= 26; ++i) isend[tail[i]] = true;
    for (i32 i = 1; i <= 26; ++i) to[n + 1][i] = n + 1;
    for (i32 i = n; i >= 1; --i) {
      for (i32 j = 1; j <= 26; ++j)
        to[i][j] = to[i + 1][j];
      to[i][a[i]] = i;
    }
    i32 ans = 0;
    for (i32 i = 1; i <= 26; ++i) dp[head[i]] = 1;
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j = 1; j <= 26; ++j) {
        if (to[i + 1][j] != n + 1)
          if (pre[to[i + 1][j]] <= i && to[i + 1][j] <= nxt[i])
            dp[to[i + 1][j]] = inc(dp[to[i + 1][j]], dp[i]);
      }
      if (isend[i]) ans = inc(ans, dp[i]);
      dp[i] = 0;
    }
    fprintf(fout, "%d\n", ans);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("subseq.in", "r");
    fout = fopen("subseq.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1468::main(), 0; }
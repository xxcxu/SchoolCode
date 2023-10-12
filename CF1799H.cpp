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
namespace Solution_Of_CF1799H {
	bool _1;
  static const i32 N = 5005;
  static const i32 P = 998244353;
  i32 n, k;
  i32 c[N], d[N];
  i32 high[1 << 6], sum[1 << 6];
  i32 size[N], f[N][7][1 << 6];
  std::vector<i32> e[N];
	bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void dfs(i32 x, i32 fa) {
    size[x] = 1;
    for (i32 y : e[x])
      if (y != fa) {
        dfs(y, x);
        size[x] += size[y];
      }
    i32 g[k + 1][1 << k] = {};
    f[x][k][0] = 1;
    for (i32 y : e[x])
      if (y != fa) {
        for (i32 S = 0; S < (1 << k); ++S)
          for (i32 T = S; T < (1 << k); T = (T + 1) | S) {
            i32 mask = S ^ T;
            g[k][T] = inc(g[k][T], mul(f[x][k][S], f[y][k][mask]));
          }
        for (i32 i = k - 1; i >= 0; --i)
          for (i32 S = 0; S < (1 << k); ++S)
            for (i32 T = S; T < (1 << k); T = (T + 1) | S) {
              i32 mask = S ^ T;
              if (high[mask] > i) continue;
              g[i][T] = inc(g[i][T], mul(f[x][i][S], f[y][k][mask]));
              g[i][T] = inc(g[i][T], mul(f[y][i][S], f[x][k][mask]));
            }
        for (i32 i = 0; i <= k; ++i)
          for (i32 S = 0; S < (1 << k); ++S)
            f[x][i][S] = g[i][S], g[i][S] = 0;
      }
    if (x != 1) {
      for (i32 i = 0; i <= k; ++i)
        for (i32 S = 0; S < (1 << k); ++S)
          for (i32 j = 0; j < i; ++j)
            if (~S >> j & 1) {
              i32 T = S & ((1 << j) - 1);
              i32 s = size[x] - sum[T];
              if (s == c[j]) g[j][S ^ (1 << j)] = inc(g[j][S ^ (1 << j)], f[x][i][S]);
              if (s == d[j] && j > high[S]) g[i][S ^ (1 << j)] = inc(g[i][S ^ (1 << j)], f[x][i][S]); 
            }
      for (i32 i = 0; i <= k; ++i)
        for (i32 S = 0; S < (1 << k); ++S)
          f[x][i][S] = inc(f[x][i][S], g[i][S]);
    }
    return void();
  }
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    k = read(); 
    for (i32 i = 0; i < k; ++i) c[i] = read(), d[i] = i ? c[i - 1] - c[i] : n - c[i];
		i64 Start_Time_Without_Read = clock();
    high[0] = -1;
    for (i32 S = 0; S < (1 << k); ++S)
      for (i32 i = 0; i < k; ++i)
        if (S >> i & 1) high[S] = i;
    for (i32 S = 1; S < (1 << k); ++S)
      sum[S] = sum[S ^ (1 << high[S])] + d[high[S]];
    dfs(1, 0);
    i32 ans = 0;
    for (i32 i = 0; i <= k; ++i)
      ans = inc(ans, f[1][i][(1 << k) - 1]);
    fprintf(fout, "%d\n", ans);
		i64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_CF1799H::main(), 0; }
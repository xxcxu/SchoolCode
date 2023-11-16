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
namespace Solution_Of_HLP1492 {
	bool _1;
	static const i32 N = 10005, M = 55;
	static const i32 P = 998244353;
	i32 n, m;
	char s[N][M];
	i32 b[M][N], c[N][M], a[M][M], deg[N];
	bool _2;
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
	i32 Gauss() {
		i32 ans = 1, t = 1;
		for (i32 i = 1; i <= m; ++i) {
			i32 p = i;
			for (i32 j = i + 1; j <= m; ++j)
				if (a[j][i]) p = j;
			if (i != p) t = -t, std::swap(a[i], a[p]);
			i32 rec = inv(a[i][i]);
			ans = mul(ans, a[i][i]);
			for (i32 j = i; j <= m; ++j)
				a[i][j] = mul(a[i][j], rec);
			for (i32 j = 1; j <= m; ++j)
				if (a[j][i] && j != i)
					for (i32 k = m; k >= i; --k)
						a[j][k] = dec(a[j][k], mul(a[j][i], a[i][k]));
		}
		return t == 1 ? ans : P - ans;
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("connect.in", "r");
    fout = fopen("connect.out", "w");
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		i64 Start_Time_Without_Read = clock();
		n = read(), m = read();
		for (i32 i = 1; i <= n; ++i) fscanf(fin, "%s", s[i] + 1);
		i32 ans = 1;
		for (i32 i = 1; i <= n; ++i) {
			for (i32 j = 1; j <= m; ++j)
				if (s[i][j] == '.') {
					++b[j][i];
					++c[i][j];
					++a[j][j];
					++deg[i];
				}
			if (!deg[i]) ans = 0;
			i32 rec = inv(deg[i]);
			for (i32 j = 1; j <= m; ++j)
				c[i][j] = mul(c[i][j], rec);
			if (i < n) ans = mul(ans, deg[i]);
		}	
		--n;
		for (i32 i = 1; i <= m; ++i)
			for (i32 j = 1; j <= n; ++j)
				if (b[i][j])
					for (i32 k = 1; k <= m; ++k)
						a[i][k] = dec(a[i][k], c[j][k]);
		fprintf(fout, "%d\n", mul(ans, Gauss()));
		i64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_HLP1492::main(), 0; }
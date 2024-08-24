#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()
FILE *fin, *fout, *ferr;
i64 read() {
	i64 t = 0, f = 0;
	char ch = fgetc(fin);
	for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
	for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
	return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
namespace Solution_Of_P2602 {
	bool _1;
	static const i32 N = 20;
	i64 L, R;
	i64 ans1[N], ans2[N];
	i64 dp[N], p10[N];
	bool _2;
	void solve(i64 x, i64 *ans) {
	    i64 n = x;
	    std::vector<i64> v;
	    while (n) v.eb(n % 10), n /= 10; 
	    i64 len = (i64)v.size();
	    for (i64 i = len - 1; i >= 0; --i) {
	      for (i64 j = 0; j < 10; ++j) ans[j] += dp[i] * v[i];
	      for (i64 j = 0; j < v[i]; ++j) ans[j] += p10[i];
	      x -= v[i] * p10[i]; ans[v[i]] += x + 1;
	      ans[0] -= p10[i];
	    }
	    return void();
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		i64 Start_Time = clock();
		L = read(), R = read();
		p10[0] = 1;
		for (i64 i = 1; i < 20 ; ++i) {
			dp[i] = dp[i - 1] * 10 + p10[i - 1];
			p10[i] = p10[i - 1] * 10;
		}
		solve(L - 1, ans1), solve(R, ans2); 
    	for (i64 i = 0; i < 10; ++i) fprintf(fout, "%lld ", ans2[i] - ans1[i]);
		i64 End_Time = clock();
		fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
		return void();
	}
}
signed main() { return Solution_Of_P2602::main(), 0; }

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
#pragma endregion
namespace Solution_Of_HLP1435 {
	bool _1;
	static const i32 N = 200005;
	i32 n, a[N];
	i64 L, R;
	bool _2;
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("game.in", "r");
    fout = fopen("game.out", "w");
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		n = read();
		L = read(), R = read();
		for (i32 i = 1; i <= n; ++i) a[i] = read();
		i64 Start_Time_Without_Read = clock();
		std::sort(a + 1, a + n + 1);
		i64 sum1 = 0, sum2 = 0;
		for (i32 i = 1; i <= n; i += 2) sum1 += a[i];
		for (i32 i = n; i >= 1; i -= 2) sum2 += a[i];
		if (sum1 < L || sum2 > R) fputs("Alice\n", fout);
		else fputs("Bob\n", fout);
		i64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_HLP1435::main(), 0; }
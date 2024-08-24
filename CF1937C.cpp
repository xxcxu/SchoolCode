#pragma region
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
namespace Solution_Of_CF1937C {
	bool _1;
	i32 n;
	bool _2;
	i32 query(i32 x, i32 y, i32 xx, i32 yy) {
		fprintf(fout, "? %d %d %d %d\n", x - 1, y - 1, xx - 1, yy - 1);
		fflush(fout);
		char t = fgetc(fin);
		while (t != '<' && t != '=' && t != '>') t = fgetc(fin);
		return t == '<' ? 1 : (t == '>' ? 2 : 0);
	}
	// = 0 || < 1 || > 2
	void solve() {
		n = read();
		i32 p1 = 1;
		for (i32 i = 2; i <= n; ++i) if (query(i, i, p1, p1) == 2) p1 = i;
		i32 *p = new int[n + 1], tot = 0;
		p[tot = 1] = 1;
		for (i32 i = 2; i <= n; ++i) {
			i32 t = query(p1, i, p1, p[1]);
			if (t == 2) p[tot = 1] = i;
			if (t == 0) p[++tot] = i;
		}
		i32 p2 = p[1];
		for (i32 i = 2; i <= tot; ++i) if (query(p[i], p[i], p2, p2) == 1) p2 = p[i];
		fprintf(fout, "! %d %d\n", p1 - 1, p2 - 1);	
		return void();
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		i64 Start_Time_Without_Read = clock();
		i32 t = read();
		while (t--) solve();
		i64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_CF1937C::main(), 0; }
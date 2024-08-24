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
namespace Solution_Of_P6216 {
	bool _1;
  static const i32 N = 3000005;
	i32 n, m;
	i32 r[N], nxt[N];
	u32 a[N], s1[N], s2[N];
	char s[N], t[N];
	bool _2;
	void init() {
		nxt[1] = 0;
		for (i32 i = 2, j = 0; i <= m; ++i) {
			while (t[j + 1] != t[i] && j) j = nxt[j];
			if (t[j + 1] == t[i]) ++j;
			nxt[i] = j;
		}
		for (i32 i = 1, j = 0; i <= n; ++i) {
			while (t[j + 1] != s[i] && j) j = nxt[j];
			if (t[j + 1] == s[i]) ++j;
			if (j == m) a[i - m + 1] = 1;
		}
		return void();
	}
	void manacher() {
		s[0] = '#', s[n + 1] = '@';
		i32 mx = 0, id = 0;
		for (i32 i = 1; i <= n; ++i) {
			r[i] = i < mx ? std::min(r[(id << 1) - i], mx - i) : 0;
			while (s[i - r[i] - 1] == s[i + r[i] + 1]) ++r[i];
			if (i + r[i] > mx) mx = i + r[i], id = i;
		}
		return void();
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		i64 Start_Time = clock();
		n = read(), m = read();
		fscanf(fin, "%s%s", s + 1, t + 1);
		init(), manacher();
		u32 ans = 0;
		for (i32 i = 1; i <= n; ++i) {
			s1[i] = s1[i - 1] + a[i];
			s2[i] = s2[i - 1] + a[i] * i;
		}
		for (i32 i = 1; i <= n; ++i) {
			i32 L = i - r[i], R = i + r[i] - m + 1;
      assert(L >= 1);
      assert(R + m - 1 <= n);
			if (L > R) continue;
			i32 mid((L + R) >> 1);
			ans += (s2[mid] - s2[L - 1]) - (s1[mid] - s1[L - 1]) * (L - 1);
			ans += (s1[R] - s1[mid]) * (R + 1) - (s2[R] - s2[mid]);
		}
		fprintf(fout, "%u\n", ans);
		i64 End_Time = clock();
		fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
		return void();
	}
}
signed main() { return Solution_Of_P6216::main(), 0; }
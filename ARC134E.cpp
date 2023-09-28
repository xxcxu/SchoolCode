#include <bits/stdc++.h>
namespace FileHeader {
	using int16 = int16_t;
	using int32 = int32_t;
	using int64 = int64_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;
	#define ep emplace
	#define eb emplace_back
	#define all(x) x.begin(), x.end()
	FILE* fin, * fout, * ferr;
	int32 read() {
		int32 t = 0, f = 0;
		char ch = fgetc(fin);
		for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
		for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
		return f ? -t : t;
	}
	class Iterator {
		public:
			Iterator(int32 _val = 0): _val(_val) {}
			bool operator !=(const Iterator &other) const { return this->_val != other._val; }
			int32 operator *() { return this->_val; }
			int32 operator ++() { return ++this->_val; }
		private:
			int32 _val;
	};
	class Range {
		public:
			Range(int32 _l = 0, int32 _r = 0): _begin(_l), _end(_r + 1) {}
			Iterator begin() { return Iterator(this->_begin); }
			Iterator end() { return Iterator(this->_end); }
		private:
			int32 _begin, _end;
	};
}
using namespace FileHeader;
namespace Solution_Of_ARC134E {
	bool _1;
	static const int32 N = 205;
	static const int32 P = 998244353;
	int32 n;
	int32 a[N], f[N][1 << 16], g[1 << 16];
	bool _2;
	int32 inc(int32 x, int32 y) { return (x + y) % P; }
	int32 dec(int32 x, int32 y) { return (x + P - y) % P; }
	int32 mul(int32 x, int32 y) { return 1LL * x * y % P; }
	bool check(int32 S) {
		if (!S) return true; // {12}
		if (~g[S]) return g[S];
		int32 max = 0;
		for (int32 i = 15; i >= 0; --i)
			if (S >> i & 1) { max = 12 * (i + 1); break; }
		for (int32 mod = 1; mod <= max; ++mod) {
			std::set<int32> s;
			for (int32 i = 0; i < 16; ++i)
				if (S >> i & 1)
					if ((12 * (i + 1)) % mod)
            s.ep((12 * (i + 1)) % mod);
			int64 m = s.size();
			bool win =
			(m == 1 && (*s.begin() == 1 || *s.begin() == 2)) ||
			(m == 2 && (*s.begin() == 4 && *s.rbegin() == 8));
			if (win) return g[S] = 1;
			for (auto it : s) if (it % 12) win = true;
			if (win) continue;
			int32 T = 0;
			for (auto it : s) T |= (1 << (it / 12 - 1));
			if (!check(T)) return g[S] = 1;
		}
		return g[S] = 0;
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		n = read();
		int32 ans = 1, factor12 = 1;
		for (int32 i = 1; i <= n; ++i) {
			a[i] = read();
			ans = mul(ans, a[i]);
			factor12 = mul(factor12, a[i] / 12);
		}
		int64 Start_Time_Without_Read = clock();
		std::memset(g, -1, sizeof g);
		int32 max = *std::max_element(a + 1, a + n + 1);
		int32 min = *std::min_element(a + 1, a + n + 1);
		ans = dec(ans, factor12);
		{ // {1}
			ans = dec(ans, 1);
		}
		{ // {2}
			if (min > 1) ans = dec(ans, 1);
		}
		{ // {4}
			if (min >= 4) ans = inc(ans, 1);
		}
		{ // {8}
			if (min >= 8) ans = inc(ans, 1);
		}
		{ // {4, 8}
			if (min >= 4) {
				int32 res = 1;
				for (int32 i = 1; i <= n; ++i)
					if (a[i] >= 8) res = mul(res, 2);
				ans = dec(ans, res);
			}
		}
		{ // {12, 24, ....}
			if (min >= 12) {
				f[0][0] = 1;
				int32 R = (1 << 16);
				for (int32 i = 1; i <= n; ++i)
					for (int32 S = 0; S < R; ++S)
						if (f[i - 1][S])
							for (int32 p = 1; 12 * p <= a[i]; ++p)
								f[i][S | (1 << (p - 1))] = inc(f[i][S | (1 << (p - 1))], f[i - 1][S]);
				for (int32 S = 0; S < R; ++S) if (check(S)) ans = inc(ans, f[n][S]);
			}
		}
    fprintf(fout, "%d\n", ans);
		int64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_ARC134E::main(), 0; }
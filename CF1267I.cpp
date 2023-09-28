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
namespace Solution_Of_CF1267I {
	bool _1;
	static const int32 N = 2 * 105;
	int32 n, ind[N];
	bool _2;
	bool query(int32 x, int32 y) {
		fprintf(fout, "? %d %d\n", x, y);
		fflush(fout);
		char ch = fgetc(fin);
		while (ch != '<' && ch != '>') ch = fgetc(fin);
		return ch == '>';
	}
	int32 opposite(int32 x) { return (x & 1) ? x + 1 : x - 1; }
	void solve() {
		n = read();
		for (int32 i = 1; i <= 2 * n; i += 2)
			ind[(i + 1) / 2] = query(i, i + 1) ? i + 1 : i;
		std::sort(ind + 1, ind + n + 1, query);
		int32 min = ind[1], max = opposite(min);
		std::iota(ind + 1, ind + 2 * n + 1, 1);
		std::swap(ind[1], ind[max]);
		std::swap(ind[2], ind[max == 2 ? 2 : min]);
		std::sort(ind + 3, ind + 2 * n + 1, query);
		query(ind[2], ind[n + 1]);
		fputs("!\n", fout), fflush(fout);
		return void(); 
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		int32 t = read();
		int64 Start_Time_Without_Read = clock();
		while (t--) solve();
		int64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_CF1267I::main(), 0; }
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
namespace Solution_Of_HLP1310 {
  bool _1;
  static const int32 N = 1005, M = 2 * N;
  static const int32 dx[] = {-1, -1, -2, -2, 1, 1, 2, 2};
  static const int32 dy[] = {2, -2, 1, -1, 2, -2, 1, -1};
  int32 n, m;
  std::map<int32, std::map<int32, int32>> step;
  int32 calc(int32 x) {
    if (x % 4 == 0) return x / 2;
    else return (x + 2) / 2;
  }
  void solve() {
    int32 nn = read(), mm = read();
    n = read() - nn, m = read() - mm;
    if (n < 0) n = -n;
    if (m < 0) m = -m;
    if (n == 0 && m == 0) fprintf(fout, "%d\n", 0);
    else if ((n == 1 && m == 0) || (n == 0 && m == 1)) fprintf(fout, "%d\n", 3);
    else if (n == 1 && m == 1) fprintf(fout, "%d\n", 2);
    else if (n == 2 && m == 2) fprintf(fout, "%d\n", 4);
    else if (n <= 2 * m && m <= 2 * n) fprintf(fout, "%d\n", (m + n) / 3 + (m + n) % 3);
    else if (n == 0 || m == 0) fprintf(fout, "%d\n", 2 * ((n + m - 2) / 4) + (n + m - 2) % 2 + 2);
    else if (n > 2 * m) fprintf(fout, "%d\n", (n - 2 * m) / 4 * 2 + (n - 2 * m) % 4 + m);
    else if (m > 2 * n) fprintf(fout, "%d\n", (m - 2 * n) / 4 * 2 + (m - 2 * n) % 4 + n);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    // int32 t = read();
    int64 Start_Time_Without_Read = clock();
    // while (t--) solve();
    solve();
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1310::main(), 0; }
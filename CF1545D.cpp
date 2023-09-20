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
namespace Solution_Of_CF1545D {
  bool _1;
  static const int32 N = 1005;
  int32 n, m;
  int64 a[N][N];
  int64 b[N], c[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (int32 i = 1; i <= m; ++i)
      for (int32 j = 1; j <= n; ++j) a[i][j] = read();
    int64 Start_Time_Without_Read = clock();
    for (int32 i = 1; i <= m; ++i)
      for (int32 j = 1; j <= n; ++j)
        b[i] += a[i][j], c[i] += a[i][j] * a[i][j];
    int64 real = -1, real2 = -1;
    for (int32 i = 2; i < m; ++i)
      if (b[i + 1] - b[i] == b[i] - b[i - 1])
        real = b[i] - b[i - 1];
    for (int32 i = 3; i < m; ++i)
      if (c[i + 1] + c[i - 1] - 2 * c[i] == c[i] + c[i - 2] - 2 * c[i - 1])
        real2 = c[i + 1] + c[i - 1] - 2 * c[i];
    assert(real != -1);
    if (real2 == -1) real2 = c[3] + c[1] - 2 * c[2];
    int32 p = -1;
    for (int32 i = 2; i <= m; ++i)
      if (b[i] - b[i - 1] != real) { p = i; break; }
    assert(p != -1);
    for (int32 i = 1; i <= n; ++i) {
      int64 newNumber = b[p - 1] + real - (b[p] - a[p][i]);
      int64 newSqr = (c[p] - a[p][i] * a[p][i]) + newNumber * newNumber;
      if (p != m && c[p + 1] + c[p - 1] - newSqr * 2 == real2) {
        fprintf(fout, "%d %lld\n", p - 1, newNumber);
        return void();
      }
      if (p == m && newSqr + c[p - 2] - c[p - 1] * 2 == real2) {
        fprintf(fout, "%d %lld\n", p - 1, newNumber);
        return void();
      }
    }
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1545D::main(), 0; }
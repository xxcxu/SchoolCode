#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using ui32 = uint32_t;
  using ui64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  i32 read() {
    i32 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
  class Iterator {
    public:
      Iterator(i32 _val = 0): _val(_val) {}
      bool operator !=(const Iterator &other) const { return this->_val != other._val; }
      i32 operator *() { return this->_val; }
      i32 operator ++() { return ++this->_val; }
    private:
      i32 _val;
  };
  class Range {
    public:
      Range(i32 _l = 0, i32 _r = 0): _begin(_l), _end(_r + 1) {}
      Iterator begin() { return Iterator(this->_begin); }
      Iterator end() { return Iterator(this->_end); }
    private:
      i32 _begin, _end;
  };
}
using namespace FileHeader;
namespace Solution_Of_CF12E {
  bool _1;
#pragma endregion
  static const i32 N = 1005;
  i32 n;
  i32 a[N][N];
  bool _2;
  void print() {
    for (i32 i = 1; i <= n; ++i, fputs("\n", fout))
      for (i32 j = 1; j <= n; ++j)
        fprintf(fout, "%d ", a[i][j]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i < n; ++i) a[i][1] = i;
    for (i32 i = 2; i < n; ++i) {
      for (i32 j = 1; j < n; ++j) a[j][i] = a[j + 1][i - 1];
      a[n - 1][i] = a[1][i - 1];
    }
    for (i32 i = 1; i < n; ++i) a[i][n] = a[n][i] = a[i][i], a[i][i] = 0;
    a[n][n] = 0;
    print();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF12E::main(), 0; }
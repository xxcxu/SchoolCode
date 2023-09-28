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
namespace Solution_Of_ARC135D {
  bool _1;
#pragma endregion
  static const i32 N = 505;
  i32 n, m;
  i64 ans;
  i64 a[N][N], b[N][N], x[N], y[N], op[N][N];
  bool _2;
  void change(i32 i, i32 j, i64 v) {
    x[i] -= v;
    y[j] -= v;
    b[i][j] += v;
    ans += std::abs(v);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        op[i][j] = (i + j) & 1 ? -1 : 1;
        a[i][j] = read();
        a[i][j] *= op[i][j];
        x[i] += a[i][j], y[j] += a[i][j];
      }
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j) {
        if (x[i] < 0 && y[j] < 0) change(i, j, std::max(x[i], y[j]));
        if (x[i] > 0 && y[j] > 0) change(i, j, std::min(x[i], y[j]));
      }
    for (i32 i = 1; i <= n; ++i) change(i, 1, x[i]);
    for (i32 i = 1; i <= m; ++i) change(1, i, y[i]);
    fprintf(fout, "%lld\n", ans);
    for (i32 i = 1; i <= n; ++i, fputs("\n", fout))
      for (i32 j = 1; j <= m; ++j)
        fprintf(fout, "%lld ", b[i][j] * op[i][j]);
    return void();
  }
}
signed main() { return Solution_Of_ARC135D::main(), 0; }
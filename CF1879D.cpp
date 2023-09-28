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
namespace Solution_Of_CF1879D {
  bool _1;
  static const int32 N = 300005;
  static const int32 P = 998244353;
  int32 inc(int32 x, int32 y) { return (x + y) % P; }
  int32 dec(int32 x, int32 y) { return (x + P - y) % P; }
  int32 mul(int32 x, int32 y) { return 1ll * x * y % P; }
  int32 n, t1[2], t2[2];
  int32 a[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read() ^ a[i - 1];
    int64 Start_Time_Without_Read = clock();
    int32 ans = 0;
    for (int32 i = 0; i < 31; ++i) {
      t1[0] = t1[1] = t2[0] = t2[1] = 0;
      ++t1[0];
      for (int32 j = 1; j <= n; ++j) {
        int32 d = (a[j] >> i) & 1;
        ans = inc(ans, mul(1 << i, dec(mul(t1[d ^ 1], j), t2[d ^ 1])));
        ++t1[d], t2[d] = inc(t2[d], j);
      }
    }
    fprintf(fout, "%d\n", ans);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1879D::main(), 0; }
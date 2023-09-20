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
namespace Solution_Of_CF1870B {
  bool _1;
  static const int32 N = 200005;
  int32 n, m;
  int32 a[N], b[N], c[N], cnt1[35], cnt2[35];
  void solve() {
    n = read(), m = read();
    for (int32 i = 1; i <= n; ++i)
      a[i] = read();
    for (int32 i = 1; i <= m; ++i)
      b[i] = read();
    for (int32 i = 0; i <= 30; ++i) {
      cnt1[i] = cnt2[i] = 0;
      for (int32 j = 1; j <= n; ++j)
        cnt1[i] += (a[j] >> i & 1);
      for (int32 j = 1; j <= m; ++j)
        cnt2[i] += (b[j] >> i & 1);
    }
    int32 xor1 = 0, xor2 = 0;
    for (int32 i = 1; i <= n; ++i) xor1 ^= a[i], xor2 ^= a[i];
    if (n & 1) {
      for (int32 i = 0; i <= 30; ++i)
        if (cnt2[i])
          if ((cnt1[i] + 1) & 1) xor2 ^= (1 << i);
      fprintf(fout, "%d %d\n", xor1, xor2);
    } else {
      for (int32 i = 0; i <= 30; ++i)
        if (cnt2[i])
          if (cnt1[i] & 1) xor1 ^= (1 << i);
      fprintf(fout, "%d %d\n", xor1, xor2);
    }
  }
  bool _2;
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
signed main() { return Solution_Of_CF1870B::main(), 0; }
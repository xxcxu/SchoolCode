#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using i128 = __int128_t;
  using ui32 = uint32_t;
  using ui64 = uint64_t;
  #define i32 i64
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
namespace Solution_Of_grid {
  bool _1;
#pragma endregion
  static const i32 N = 1000005;
  i32 n, m;
  i128 f[N];
  bool _2;
  void write(i128 x) {
    if (x < 0) { fputc('-', fout); x = -x; }
    if (x > 9) write(x / 10);
    fputc(char('0' + (x % 10)), fout);
    return void();
  }
  void solve() {
    n = read(), m = read();
    i128 ans = 0;
    if (n < m) std::swap(n, m);
    for (i32 i = 1; i <= n; ++i) {
      i128 sa = 0, sb = 0;
      for (i32 j = 1; j <= n / i; ++j) sa += n - 1ll * i * j;
      for (i32 j = 1; j <= m / i; ++j) sb += m - 1ll * i * j;
      f[i] = sa * sb * 2 + sa * m + sb * n;
    }
    for (i32 i = n; i >= 1; --i)
      for (i32 j = i * 2; j <= n; j += i)
        f[i] -= f[j];
    for (i32 i = 1; i <= n; ++i)
      ans += f[i] * (n * m - i * 2) * i;
    write(ans);
    fputs("\n", fout);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("grid.in", "r");
    // fout = fopen("grid.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_grid::main(), 0; }
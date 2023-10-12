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
  i64 read() {
    i64 t = 0, f = 0;
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
namespace Solution_Of_creek {
  bool _1;
#pragma endregion
  static const i32 N = 1000005;
  i32 n; i64 C, D;
  i64 a[N], b[N], c[N];
  bool _2;
  i64 calc(i32 x) {
    return 1ll * (x + 1) * x / 2;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("creek.in", "r");
    // fout = fopen("creek.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), C = read(), D = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), b[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) c[i] = a[i] + 1ll * i * D - b[i] - 1ll * i * C;
    std::sort(c + 1, c + n + 1, std::greater<i64>());
    i64 res = 0, ans = 0;
    for (i32 i = 1; i <= n; ++i) res += b[i] + 1ll * i * C;
    for (i32 i = 0; i <= n; ++i) {
      if (i) res += c[i];
      ans = std::max(ans, res - calc(i) * D - calc(n - i) * C);
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_creek::main(), 0; }
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
namespace Solution_Of_CF1882C {
  bool _1;
#pragma endregion
  static const i32 N = 200005;
  i32 n;
  i32 a[N];
  bool _2;
  void solve() {
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    if (a[1] >= 0) {
      i64 ans = 0;
      for (i32 i = 1; i <= n; ++i) if (a[i] > 0) ans += a[i];
      fprintf(fout, "%lld\n", ans);
    } else {
      if (a[1] < 0 && a[2] <= 0) {
        i64 ans = 0;
        for (i32 i = 1; i <= n; ++i) if (a[i] > 0) ans += a[i];
        fprintf(fout, "%lld\n", ans);
      } else {
        i64 ans1 = 0;
        for (i32 i = 1; i <= n; ++i) if (a[i] > 0) ans1 += a[i];
        ans1 += a[1];
        i64 ans2 = 0;
        for (i32 i = 3; i <= n; ++i) if (a[i] > 0) ans2 += a[i];
        fprintf(fout, "%lld\n", std::max(ans1, ans2));
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1882C::main(), 0; }
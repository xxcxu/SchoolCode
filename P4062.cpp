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
namespace Solution_Of_P4062 {
  bool _1;
#pragma endregion
  static const i32 N = 500005;
  i32 n, ignore;
  i32 a[N];
  i64 s1[N * 2], s2[N * 2], s3[N * 2];
  std::vector<i32> pos[N];
  void add(i32 x, i32 v) {
    for (i32 i = x; i <= 2 * n + 1; i += i & -i) {
      s1[i] += 1ll * v;
      s2[i] += 1ll * v * x;
      s3[i] += 1ll * v * x * x;
    }
    return void();
  }
  i64 ask(i32 x) {
    i64 ans = 0;
    for (i32 i = x; i >= 1; i -= i & -i) {
      ans += 1ll * (x + 1) * (x + 2) * s1[i];
      ans -= 1ll * (2 * x + 3) * s2[i];
      ans += 1ll * s3[i];
    }
    return ans / 2;
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), ignore = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) pos[a[i]].eb(i);
    i64 Start_Time_Without_Read = clock();
    i32 D = n + 1;
    i64 ans = 0;
    for (i32 i = 0; i < n; ++i) {
      pos[i].eb(n + 1);
      static i32 lst;
      lst = 0;
      for (i32 j = 0; j < size(pos[i]); ++j) {
        i32 r = 2 * j - lst + D, l = 2 * j - pos[i][j] + 1 + D;
        ans += ask(r - 1) - (l >= 3 ? ask(l - 2) : 0);
        add(l, 1);
        add(r + 1, -1);
        lst = pos[i][j];
      }
      lst = 0;
      for (i32 j = 0; j < size(pos[i]); ++j) {
        i32 r = 2 * j - lst + D, l = 2 * j - pos[i][j] + 1 + D;
        add(l, -1);
        add(r + 1, 1);
        lst = pos[i][j];
      }
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P4062::main(), 0; }
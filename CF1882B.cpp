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
namespace Solution_Of_CF1882B {
  bool _1;
#pragma endregion
  static const i32 N = 55;
  i32 n;
  i32 a[N];
  std::set<i32> set, s[N];
  bool _2;
  void solve() {
    n = read();
    std::vector<i32> numric;
    set.clear();
    for (i32 i = 1; i <= n; ++i) {
      a[i] = read();
      s[i].clear();
      for (i32 j = 1; j <= a[i]; ++j) {
        static i32 x;
        x = read();
        s[i].ep(x);
        set.ep(x);
      } 
    }
    auto merge = [&](std::set<i32> &a, std::set<i32> b)->void {
      if (size(a) < size(b)) std::swap(a, b);
      for (auto it : b) a.ep(it);
      return void();
    };
    i32 ans = 0;
    for (i32 i : set) {
      std::set<i32> now;
      for (i32 j = 1; j <= n; ++j) {
        if (!s[j].count(i))
          merge(now, s[j]);
      }
      ans = std::max(ans, (i32)size(now));
    }
    fprintf(fout, "%d\n", ans);
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
signed main() { return Solution_Of_CF1882B::main(), 0; }
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
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
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
namespace Solution_Of_index {
  bool _1;
#pragma endregion
  static const i32 N = 1000005;
  i32 n, k;
  i32 a[N], s[N], fa[N];
  std::vector<i32> vec[N], pos[N], add[N];
  bool _2;
  i32 _find(i32 x) {
    if (fa[x] == x) return x;
    return fa[x] = _find(fa[x]);
  }
  void _add(i32 x, i32 v) {
    for (; x <= n; x += x & -x)
      s[x] += v;
    return void();
  }
  i32 _ask(i32 x) {
    i32 ans = 0;
    for (; x >= 1; x -= x & -x)
      ans += s[x];
    return ans;
  }
  void _print(i32 x) {
    if (k <= 0 || x <= 0) fprintf(fout, "%d ", x);
    else --k, _print(x - 1), _print(x - 1);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    a[0] = 31;
    for (i32 i = 1; i <= n; ++i) fa[i] = i;
    for (i32 i = 1; i <= n; ++i) {
      pos[a[i]].eb(i);
      for (i32 j = a[i]; j < a[i - 1]; ++j) vec[j].eb(i);
    }
    for (i32 i = 0; i < 30; ++i) {
      for (i32 j : pos[i]) {
        _add(j, 1u << i);
        if (j < n && a[j + 1] <= i) fa[j] = _find(j + 1);
        if (j > 1 && a[j - 1] <= i) fa[j - 1] = _find(j);
      }
      for (i32 j : vec[i]) {
        i32 s = _ask(_find(j)) - _ask(j - 1);
        if (s % (1 << (i + 1))) {
          _add(_find(j), 1u << i);
          add[_find(j)].eb(i);
          --k;
        }
      }
    }
    for (i32 i = 1; i <= n; ++i) {
      fprintf(fout, "%d ", a[i]);
      for (i32 j : add[i]) _print(j);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_index::main(), 0; }
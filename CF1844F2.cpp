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
namespace Solution_Of_CF1844F2 {
  bool _1;
#pragma endregion
  static const i32 N = 200005;
  i32 n, c;
  i32 a[N], b[N], l[N], r[N];
  bool _2;
  bool check(i32 x) {
    if (l[x] < 1 || r[x] > n || a[r[x]] - a[l[x]] < c) return false;
    return true;
  }
  void solve() {
    n = read(), c = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    if (c >= 0) {
      std::sort(a + 1, a + n + 1);
    } else {
      std::sort(a + 1, a + n + 1, std::greater<i32>());
      l[n + 1] = n + 1;
      r[0] = 2;
      for (i32 i = 2; i <= n; ++i) {
        l[i] = i - 1 - (i == 2);
        r[i] = i + 1;
      }
      b[1] = a[1];
      std::set<std::tuple<i32, i32>> s;
      for (i32 i = 3; i < n; ++i) if (a[r[i]] - a[l[i]] >= c) s.ep(a[i], i);
      for (i32 i = 2; i <= n; ++i) {
        auto it = s.lower_bound(std::make_tuple(b[i - 1] + c, 0));
        auto pos = -1;
        if (it == s.end()) pos = r[0];
        else pos = std::get<1>(*it), s.erase(it);
        b[i] = a[pos];
        i32 L = l[pos], R = r[pos];
        l[R] = L, r[L] = R;
        if (!check(L)) s.erase(std::make_tuple(a[L], L));
        if (!check(R)) s.erase(std::make_tuple(a[R], R));
      }
      for (i32 i = 1; i <= n; ++i) a[i] = b[i];
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d%c", a[i], " \n"[i == n]);
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
signed main() { return Solution_Of_CF1844F2::main(), 0; }
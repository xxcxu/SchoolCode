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
namespace Solution_Of_ {
  bool _1;
#pragma endregion
  static const i32 N = 2505;
  i32 n, m;
  i32 a[N], b[N];
  void change(i32 n, i32 p) {
    for (i32 j = p + 1; j <= n; ++j) b[j - p] = a[j];
    b[n - p + 1] = a[p];
    for (i32 j = 1; j < p; ++j) b[j + n - p + 1] = a[j];
    for (i32 j = 1; j <= n; ++j) a[j] = b[j];
    return void();
  }
  i32 find(i32 n, i32 x) {
    for (i32 i = 1; i <= n; ++i)
      if (a[i] == x)
        return i;
    return 0;
  }
  std::vector<i32> solve(i32 n) {
    std::vector<i32> ret;
    for (i32 i = 1; i < n; ++i) {
      i32 p = find(n, i);
      if (p < n) {
        ret.eb(p + 1);
        change(n, p + 1);
      }
      p = find(n, i + 1);
      ret.eb(p);
      change(n, p);
    }
    return ret;
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    std::vector<i32> path1 = solve(n);
    for (i32 i = 1; i <= m; ++i) a[i] = read();
    std::vector<i32> path2 = solve(m);
    i64 Start_Time_Without_Read = clock();
    if ((n + 1 & 1) && (m + 1 & 1) && (size(path1) & 1) != (size(path2) & 1))
      return fputs("-1", fout), void();
    if ((size(path1) & 1) != (size(path2) & 1)) {
      for (i32 i = 1; i <= (n & 1 ? n : m); ++i)
        ((n & 1) ? path1 : path2).eb(1);
    }
    i32 nn = size(path1), mm = size(path2);
    fprintf(fout, "%d\n", std::max(nn, mm));
    if (nn < mm) {
      for (i32 i = 0; i < nn; ++i) fprintf(fout, "%d %d\n", path1[i], path2[i]);
      for (i32 i = nn; i < mm; ++i) fprintf(fout, "%d %d\n", (i & 1 ? n : 1), path2[i]);
    } else {
      for (i32 i = 0; i < mm; ++i) fprintf(fout, "%d %d\n", path1[i], path2[i]);
      for (i32 i = mm; i < nn; ++i) fprintf(fout, "%d %d\n", path1[i], (i & 1 ? m : 1));
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }
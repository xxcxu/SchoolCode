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
namespace Solution_Of_uiharu {
  bool _1;
#pragma endregion
  static const i32 N = 1005, Q = 500005;
  i32 n, q, cnt;
  i32 v[Q], ans[Q], p[N], row[N], col[N];
  std::vector<std::array<i32, 2>> pos[N * N + Q];
  std::vector<i32> querys[N * N + Q];
  i32 a[N][N], b[N * N + Q];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), q = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        a[i][j] = read(), b[++cnt] = a[i][j];
    for (i32 i = 1; i <= q; ++i) v[i] = read(), b[++cnt] = v[i];
    i64 Start_Time_Without_Read = clock();
    std::sort(b + 1, b + cnt + 1);
    cnt = std::unique(b + 1, b + cnt + 1) - b - 1;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        a[i][j] = std::lower_bound(b + 1, b + cnt + 1, a[i][j]) - b;
    for (i32 i = 1; i <= q; ++i) v[i] = std::lower_bound(b + 1, b + cnt + 1, v[i]) - b;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= n; ++j)
        pos[a[i][j]].push_back({i, j});
    for (i32 i = 1; i <= q; ++i) querys[v[i]].eb(i);
    i32 empty = n;
    i32 res = 0;
    for (i32 i = cnt; i >= 1; --i) {
      for (const auto &[x, y] : pos[i]) {
        ++row[y];
        if (row[y] == 1) {
          p[y] = x;
          --empty;
        } else {  
          ++col[x];
          res = std::max(res, col[x]);
          if (row[y] == 2) ++col[p[y]], res = std::max(res, col[p[y]]);
        }
      }
      for (const auto &id : querys[i]) ans[id] = std::min(empty, res) + (n - empty);
    }
    for (i32 i = 1; i <= q; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_uiharu::main(), 0; }
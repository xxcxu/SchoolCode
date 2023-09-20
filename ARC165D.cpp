#include <bits/stdc++.h>
#include <atcoder/all>
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
namespace Solution_Of_ARC165D {
  static const int32 N = 2005;
  bool _1;
  int32 n, m;
  int32 fa[N];
  std::array<int32, 4> a[N];
  bool _2;
  int32 find(int32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void merge(int32 x, int32 y) {
    x = find(x), y = find(y);
    if (x == y) return void();
    fa[y] = x;
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (int32 i = 1; i <= m; ++i)
      a[i][0] = read(), a[i][1] = read(), a[i][2] = read(), a[i][3] = read();
    int64 Start_Time_Without_Read = clock();
    for (int32 i = 1; i <= n; ++i) fa[i] = i;
    while (true) {
      atcoder::scc_graph g(n + 1);
      for (int32 i = 1; i <= m; ++i) {
        while (a[i][0] <= a[i][1] && a[i][2] <= a[i][3] && find(a[i][0]) == find(a[i][2])) ++a[i][0], ++a[i][2];
        if (a[i][0] <= a[i][1] && a[i][2] <= a[i][3]) g.add_edge(find(a[i][0]), find(a[i][2]));
      }
      auto scc = g.scc();
      bool flag = true;
      for (auto now : scc)
        if (now.size() > 1)
          for (auto node : now) merge(now.front(), node), flag = false;
      if (flag) break;
    }
    for (int32 i = 1; i <= m; ++i)
      if (a[i][2] > a[i][3]) return fputs("No\n", fout), void();
    fputs("Yes\n", fout);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_ARC165D::main(), 0; }
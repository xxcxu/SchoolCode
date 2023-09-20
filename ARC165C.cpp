#include <bits/stdc++.h>
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
namespace Solution_Of_ARC165C {
  bool _1;
  static const int32 N = 200005;
  static const int32 inf32 = 2000000000;
  int32 n, m, col[N], min[N][2];
  bool flag;
  std::vector<std::array<int32, 2>> e[N];
  bool _2;
  void dfs(int32 x, int32 mid) {
    for (auto &[y, z] : e[x]) {
      if (z >= mid) continue;
      if (~col[y]) {
        if (col[y] == col[x])
          { flag = true; return void(); }
      }
      else {
        col[y] = col[x] ^ 1;
        dfs(y, mid);
      } 
    }
    return void();
  }
  bool check(int32 mid) {
    std::memset(col, -1, sizeof col);  
    flag = false;
    for (int32 i = 1; i <= n; ++i) {
      if (~col[i]) continue;
      col[i] = 0;
      dfs(i, mid);
    }
    if (flag) return false;
    for (int32 i = 1; i <= n; ++i) min[i][0] = min[i][1] = inf32 / 2;
    auto update = [&](int32 x, int32 v)->void {
      if (v < min[x][0]) min[x][1] = min[x][0], min[x][0] = v;
      else min[x][1] = std::min(min[x][1], v);
      return void();
    };
    for (int32 i = 1; i <= n; ++i)
      for (auto &[j, k] : e[i])
        if (col[i] != col[j]) update(i, k);
    int32 ans = inf32;
    for (int32 i = 1; i <= n; ++i)
      ans = std::min(ans, min[i][0] + min[i][1]);
    return ans >= mid;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (int32 i = 1; i <= m; ++i) {
      static int32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].push_back({v, w});
      e[v].push_back({u, w});
    }
    int64 Start_Time_Without_Read = clock();
    int32 l = 0, r = inf32, ans = -1;
    while (l <= r) {
      int32 mid(l + ((r - l) >> 1));
      if (check(mid)) ans = mid, l = mid + 1;
      else r = mid - 1;
    }
    fprintf(fout, "%d\n", ans);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_ARC165C::main(), 0; }
#include <bits/stdc++.h>
namespace FileHeader {
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
namespace Solution_Of_HLP1287 {
  static const int32 N = 100005;
  static const int64 inf64 = 0x3f3f3f3f3f3f3f3f;
  int32 n, m, k;
  int32 col[N];
  int64 dp[N][2];
  std::vector<std::array<int32, 2>> e[N];
  void dfs(int32 x, int32 fa) {
    dp[0][0] = dp[0][1] = 0;
    if (col[x]) dp[x][2 - col[x]] = inf64;
    for (auto &[y, w] : e[x]) {
      if (y == fa) continue;
      dfs(y, x);
      for (int32 i = 0; i < 2; ++i) {
        int64 now = inf64;
        for (int32 j = 0; j < 2; ++j)
          now = std::min(now, dp[y][j] + (i != j) * w);
        dp[x][i] += now;
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    n = read();
    for (int32 i = 1; i < n; ++i) {
      static int32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].push_back({v, w});
      e[v].push_back({u, w});
    }
    m = read();
    for (int32 i = 1; i <= m; ++i) {
      static int32 x;
      x = read();
      col[x] = 1;
    }
    k = read();
    for (int32 i = 1; i <= k; ++i) {
      static int32 x;
      x = read();
      col[x] = 2;
    }
    dfs(1, 0);
    fprintf(fout, "%lld\n", std::min(dp[1][0], dp[1][1]));
    return void();
  }
}
signed main() { return Solution_Of_HLP1287 ::main(), 0; }
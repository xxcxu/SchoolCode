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
namespace Solution_Of_CF1882D {
  bool _1;
#pragma endregion
  static const i32 N = 200005;
  i32 n;
  i32 a[N], size[N];
  i64 dp[N], ans[N], res[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 f, i32 d) {
    size[x] = 1;
    dp[x] = 0;
    for (const auto &y : e[x] | std::views::filter([&](auto &&y)->bool { return y != f; })) {
      dfs(y, x, d);
      dp[x] += dp[y];
      if ((a[y] >> d & 1) != (a[x] >> d & 1)) dp[x] += size[y];
      size[x] += size[y];
    }
    return void();
  }
  void dfs2(i32 x, i32 f, i32 d) {
    for (const auto &y : e[x] | std::views::filter([&](auto &&y)->bool { return y != f; })) {
      res[y] = res[x];
      if ((a[y] >> d & 1) != (a[x] >> d & 1)) res[y] += n - 2 * size[y];
      dfs2(y, x, d);
    }
    return void();
  }
  void solve() {
    n = read();
    for (i32 i = 1; i <= n; ++i) e[i].clear();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    for (i32 i = 1; i <= n; ++i) res[i] = 0, ans[i] = 0;
    for (i32 i = 0; i < 30; ++i) {
      dfs(1, 0, i);
      res[1] = dp[1];
      dfs2(1, 0, i);
      for (i32 j = 1; j <= n; ++j) ans[j] += (1ull << i) * res[j];
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%lld%c", ans[i], " \n"[i == n]);
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
signed main() { return Solution_Of_CF1882D::main(), 0; }
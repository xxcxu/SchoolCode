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
namespace Solution_Of_match {
  bool _1;
#pragma endregion
  static const i32 N = 1000005;
  i32 n, m, vis[N], dep[N], anc[N][26];
  std::vector<i32> e[N];
  bool flag;
  bool _2;
  void dfs1(i32 x) {
    for (i32 i = 1; i <= 25; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (i32 y : e[x]) {
      if (dep[y]) continue;
      dep[y] = dep[x] + 1;
      anc[y][0] = x;
      dfs1(y);
    }
    return void();
  }
  i32 lca(i32 x, i32 y) { 
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 25; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 25; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  void dfs2(i32 x) {
    vis[x] = true;
    for (i32 y : e[x]) {
      if (vis[y]) {
        i32 l = lca(x, y);
        if (dep[x] + dep[y] - 2 * dep[l] == 2) flag = true;
        continue;
      }
      dfs2(y);
    }
    return void();
  }
  void solve() {
    flag = false;
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) e[i].clear(), dep[i] = vis[i] = 0;
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    i32 max = 0;
    for (i32 i = 1; i <= n; ++i)
      max = std::max(max, i32(e[i].size()));
    for (i32 i = 1; i <= n; ++i) {
      if (dep[i]) continue;
      dep[i] = 1, anc[i][0] = 0;
      dfs1(i);
    }
    for (i32 i = 1; i <= n; ++i) {
      if (vis[i]) continue;
      dfs2(i);
    }
    if (max >= 3) return fprintf(fout, "%d\n", max), void();
    if (flag) return fputs("3\n", fout), void();
    if (max == 2) return fputs("2\n", fout), void();
    for (i32 i = 1; i <= n; ++i)
      if (e[i].size() == 2)
        return fputs("3\n", fout), void();
    fputs(m ? "1\n" : "0\n", fout);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("match2.in", "r");
    // fout = fopen("match2.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_match ::main(), 0; }
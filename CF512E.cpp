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
namespace Solution_Of_CF512E {
  bool _1;
  static const int32 N = 1005;
  int32 n;
  bool e[N][N];
  std::vector<std::array<int32, 2>> v1, v2;
  bool _2;
  void solve(std::vector<std::array<int32, 2>> &vec, int32 op) {
    std::queue<std::array<int32, 2>> q;
    std::memset(e, 0, sizeof e);
    for (int32 i = 1; i <= n; ++i) {
      int32 prev = (i == 1 ? n : i - 1);
      e[i][prev] = e[prev][i] = true;
    }
    for (int32 i = 1; i <= n - 3; ++i) {
      static int32 u, v;
      u = read(), v = read();
      e[u][v] = e[v][u] = true;
      if (u != 1 && v != 1) q.push({u, v});
    }
    while (q.size()) {
      auto& [u, v] = q.front();
      q.pop();
      if (!e[u][1] || !e[v][1]) {
        q.push({u, v});
        continue;
      }
      int32 id = -1;
      for (int32 to = 2; to <= n; ++to) {
        if (!e[u][to]) continue;
        if (to == v) continue;
        if (e[to][v]) { id = to; break; }
      }
      if (id == -1) {
        q.push({u, v});
        continue;
      }
      e[u][v] = e[v][u] = 0;
      e[1][id] = e[id][1] = true;
      if (!op) vec.push_back({u, v});
      else vec.push_back({1, id});
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    int64 Start_Time_Without_Read = clock();
    solve(v1, 0), solve(v2, 1);
    std::reverse(all(v2));
    fprintf(fout, "%lld\n", v1.size() + v2.size());
    for (auto it : v1) fprintf(fout, "%d %d\n", it[0], it[1]);
    for (auto it : v2) fprintf(fout, "%d %d\n", it[0], it[1]);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF512E::main(), 0; }
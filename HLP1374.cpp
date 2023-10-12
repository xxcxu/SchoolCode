#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using ui32 = uint32_t;
  using ui64 = uint64_t;
  using pii = std::pair<i32, i32>;
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
namespace Solution_Of_HLP1374 {
  bool _1;
#pragma endregion
  static const i32 N = 200005;
  static const i32 inf32 = 2000000001;
  i32 n, m, k;
  i32 d[N], _dist[N], deg[N];
  bool spc[N], vis[N];
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
  std::priority_queue<i32> s[N];
  std::vector<pii> e[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), k = read();
    std::fill(_dist + 1, _dist + n + 1, inf32);
    for (i32 i = 1; i <= k; ++i) {
      static i32 x;
      x = read();
      spc[x] = true;
      q.ep(_dist[x] = 0, x);
    }
    for (i32 i = 1; i <= n; ++i) d[i] = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      e[u].eb(v, w), e[v].eb(u, w);
      ++deg[u], ++deg[v];
    }
    for (i32 i = 1; i <= n; ++i) d[i] = std::min(d[i], deg[i]);
    while (q.size()) {
      i32 u = q.top().second; q.pop();
      if (_dist[u] == inf32) continue;
      if (vis[u]) continue;
      vis[u] = true;
      for (const pii &node : e[u]) {
        i32 v = node.first, w = node.second;
        if (spc[v]) continue;
        if (vis[v]) continue;
        i32 dis = _dist[u] + w;
        s[v].ep(dis);
        while ((i32)s[v].size() > d[v] + 1) s[v].pop();
        while ((i32)s[v].size() == d[v] + 1 && s[v].top() < _dist[v]) {
          _dist[v] = s[v].top();
          q.ep(_dist[v], v);
        }
      }
    }
    if (_dist[1] == inf32) fputs("-1\n", fout);
    else fprintf(fout, "%d\n", _dist[1]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1374::main(), 0; }
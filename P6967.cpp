#include <bits/stdc++.h>
namespace FileHeader {
  using int16 = int16_t;
  using int32 = int32_t;
  using int64 = int64_t;
  using uint32 = uint32_t;
  using uint64 = uint64_t;
  #define int32 int64
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
namespace Solution_Of_P6967 {
  bool _1;
  static constexpr int32 N = 100005, E = 100005 * 3;
  static constexpr int32 inf32 = 0x3f3f3f3f;
  static constexpr int64 inf64 = 0x3f3f3f3f3f3f3f3f;
  int32 n, m, ms, me;
  int32 a[N], b[N];
  int32 s, t, V, cnt = -1;
  int64 dist[N];
  int32 head[N];
  bool vis[N];
  struct edge {
    int32 to, f, cost, next;
    edge(int32 to = 0, int32 f = 0, int32 cost = 0, int32 next = 0):
      to(to), f(f), cost(cost), next(next) {}
  } e[E << 1];
  void add_edge(int32 u, int32 v, int32 f, int32 c) {
    e[++cnt] = edge(v, f, c, head[u]);
    head[u] = cnt;
    e[++cnt] = edge(u, 0, -c, head[v]);
    head[v] = cnt;
  }
  bool spfa() {
    for (int32 i = 0; i <= V; ++i)
      dist[i] = inf64, vis[i] = false;
    std::queue<int32> q;
    dist[s] = 0;
    q.emplace(s);
    while (q.size()) {
      int32 x = q.front();
      q.pop();
      vis[x] = false;
      for (int32 i = head[x]; ~i; i = e[i].next) {
        auto &y = e[i].to, &co = e[i].cost;
        if (e[i].f && dist[y] > dist[x] + co) {
          dist[y] = dist[x] + co;
          if (!vis[y]) vis[y] = true, q.emplace(y);
        }
      }
    }
    return dist[t] != inf64;
  }
  int32 dfs(int32 x, int32 cf, int64 &cost) {
    if (x == t) return cf;
    vis[x] = true;
    int32 res = cf;
    for (int32 i = head[x]; ~i; i = e[i].next) {
      auto &y = e[i].to, &co = e[i].cost;
      if (!vis[y] && e[i].f && dist[y] == dist[x] + co) {
        int32 nf = dfs(y, std::min(e[i].f, res), cost);
        if (nf) {
          e[i].f -= nf;
          e[i ^ 1].f += nf;
          res -= nf;
          cost += 1LL * nf * co;
          if (!res) break;
        }
      }
    }
    return cf - res;
  }
  int64 mcmf() {
    int64 cost = 0;
    int32 flow = 0;
    while (spfa()) {
      std::memset(vis, 0, sizeof vis);
      flow += dfs(s, inf64, cost);
    }
    return cost;
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("data.in", "r");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    std::memset(head, -1, sizeof head);
    n = read(), m = read(), ms = read(), me = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    for (int32 i = 1; i <= n; ++i) b[i] = read();
    int64 Start_Time_Without_Read = clock();
    int64 sum = 0;
    for (int32 i = 1; i <= n; ++i) sum += a[i];
    int32 flow = m - ms;
    s = 0, t = n + 1, V = n + 1;
    add_edge(s, 1, flow, 0);
    for (int32 i = 1; i < m; ++i) add_edge(i, i + 1, flow, 0);
    for (int32 i = m; i <= n; ++i) add_edge(i, i + 1, flow - me, 0);  
    for (int32 i = 1; i <= n; ++i) add_edge(i, std::min(i + m, t), 1, a[i] - b[i]);
    fprintf(fout, "%lld\n", sum - mcmf());
    for (int32 j = 1; j <= n; ++j) {
      bool flag = false;
      for (int32 i = head[j]; ~i; i = e[i].next) {
        if (e[i].cost == a[j] - b[j]) {
          flag = e[i].f;
          break;
        }
      }
      fputs(flag ? "S" : "E", fout);
    }
    fputs("\n", fout);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P6967::main(), 0; }
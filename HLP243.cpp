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
  int read() {
    int t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
}
using namespace FileHeader;
namespace Solution_Of_HLP243 {
  static const int32 N = 1000005;
  int32 n, k, q;
  int32 u[N], d[N], ans[N];
  int32 e[N], s[N], mi[N], ma[N], fa[N]; // dsu
  std::vector<int32> poker[N];
  std::vector<std::array<int32, 2>> querys[N];
  int32 find(int32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void merge(int32 x, int32 y) {
    x = find(x), y = find(y);
    if (x == y) return void();
    if (s[x] > s[y]) std::swap(x, y);
    fa[x] = y;
    mi[y] = std::min(mi[y], mi[x]);
    ma[y] = std::max(ma[y], ma[x]);
    s[y] += s[x];
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    n = read(), k = read();
    std::iota(fa + 1, fa + n + 1, 1);
    std::iota(mi + 1, mi + n + 1, 1);
    std::iota(ma + 1, ma + n + 1, 1);
    std::fill(s + 1, s + n + 1, 1);
    std::memset(e, 0, (n + 1) * sizeof(int32));
    for (int32 i = 1; i <= k; ++i)
      u[i] = read(), d[i] = read();
    for (int32 i = 1; i <= k; ++i)
      merge(u[i], d[i]);
    for (int32 i = 1; i <= k; ++i)
      if (find(u[i]) == find(d[i]))
        ++e[find(u[i])];
    for (int32 i = 1; i <= n; ++i)
      if (find(i) == i)
        if (e[i] == s[i] - 1)
          poker[ma[i]].eb(mi[i]);
    q = read();
    for (int32 i = 1; i <= q; ++i) {
      static int32 l, r;
      l = read(), r = read();
      querys[r].push_back({l, i});
    }
    int32 max_l = 0;
    for (int32 i = 1; i <= n; ++i) {
      for (auto &j : poker[i]) max_l = std::max(max_l, j);
      for (auto &[l, id] : querys[i]) ans[id] = max_l >= l;
    }
    for (int32 i = 1; i <= q; ++i) fputs(ans[i] ? "No\n" : "Yes\n", fout);
    return void();
  }
}
signed main() { return Solution_Of_HLP243::main(), 0; }
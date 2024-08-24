#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()
FILE *fin, *fout, *ferr;
i32 read() {
  i32 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
namespace Solution_Of_tree {
  bool _1;
  static const i32 N = 100005;
  i32 n, m;
  i32 bel[N], col[N], dep[N], anc[N][22];
  i32 op[N], v[N];
  i64 f[N][2], g[N][2], size[N][2];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    anc[x][0] = fa;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (i32 y : e[x])
      if (y != fa) {
        dep[y] = dep[x] + 1;
        dfs(y, x);
      }
    return void();
  }
  i32 lca(i32 x, i32 y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (i32 i = 21; i >= 0; --i)
      if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (i32 i = 21; i >= 0; --i)
      if (anc[x][i] != anc[y][i])
        x = anc[x][i], y = anc[y][i];
    return anc[x][0];
  }
  i32 dis(i32 x, i32 y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
  void tree(i32 x, i32 fa) {
    size[x][0] = size[x][1] = 0;
    f[x][0] = f[x][1] = 0;
    for (auto &y : e[x])
      if (y != fa) {
        tree(y, x);
        f[x][0] += f[y][0] + size[y][0];
        f[x][1] += f[y][1] + size[y][1];
        size[x][0] += size[y][0];
        size[x][1] += size[y][1];
      }
    ++size[x][col[x]];
    return void();
  }
  void tree2(i32 x, i32 fa) {
    for (auto &y : e[x])
      if (y != fa) {
        g[y][0] = (g[x][0] - (f[y][0] + size[y][0])) + (f[y][0] + (size[1][0] - size[y][0]));
        g[y][1] = (g[x][1] - (f[y][1] + size[y][1])) + (f[y][1] + (size[1][1] - size[y][1]));
        tree2(y, x);
      } 
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tree.in", "r");
    fout = fopen("tree.out", "w");
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) col[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 1);
    for (i32 i = 1; i <= m; ++i) op[i] = read(), v[i] = read();
    i32 l = (i32)std::sqrt(m);
    std::set<i32> s;
    for (i32 i = 1; i <= m; ++i) bel[i] = (i - 1) / l + 1;
    for (i32 i = 1; i <= m; ++i) {
      if (bel[i] != bel[i - 1]) {
        for (auto it : s) col[it] ^= 1; 
        s.clear();
        tree(1, 1);
        g[1][0] = f[1][0], g[1][1] = f[1][1];
        tree2(1, 1);
      }
      if (op[i] == 1) {
        auto it = s.find(v[i]);
        if (it != s.end()) s.erase(it);
        else s.ep(v[i]);
      } else {
        i32 flag = 0;
        if (s.find(v[i]) != s.end()) flag = 1; 
        i64 ans = g[v[i]][col[v[i]] ^ (flag)];
        for (auto it : s) {
          if (col[it] != (col[v[i]] ^ flag)) ans += dis(it, v[i]);
          else ans -= dis(it, v[i]);
        }
        fprintf(fout, "%lld\n", ans);
      }
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_tree::main(), 0; }
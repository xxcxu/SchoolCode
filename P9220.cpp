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
namespace Solution_Of_P9220 {
  static const i32 N = 100005;
  i32 n, m;
  i32 in[N], col[N], col2[N];
  i32 tsp, top, scc;
  i32 dfn[N], low[N], stk[N], ins[N], bel[N];
  std::vector<i32> e[N], g[N];
  bool OneToZero;
  bool vis[N];
  bool tarjan(i32 x) {
    dfn[x] = low[x] = ++tsp;
    stk[++top] = x, ins[x] = true;
    for (i32 y : e[x])
      if (!dfn[y]) {
        if (!tarjan(y)) return false;
        low[x] = std::min(low[x], low[y]);
      } else if (ins[y]) low[x] = std::min(low[x], dfn[y]);
    if (dfn[x] == low[x]) {
      i32 c = col[x], u;
      ++scc;
      do {
        u = stk[top--];
        if (col[u] != c) return false;
        bel[u] = scc;
        ins[u] = false;
      } while (u != x);
      col2[scc] = c; 
    }
    return true;
  }
  bool CheckAllWhite() { for (i32 i = 1; i <= n; ++i) if (col[i]) return false; return true; }
  bool CheckAllBlack() { for (i32 i = 1; i <= n; ++i) if (!col[i]) return false; return true; }
  void clear(i32 n) {
    OneToZero = true;
    top = tsp = scc = 0;
    for (i32 i = 1; i <= n; ++i) in[i] = 0;
    for (i32 i = 1; i <= n; ++i) dfn[i] = low[i] = stk[i] = ins[i] = bel[i] = 0;
    for (i32 i = 1; i <= n; ++i) vis[i] = false;
    for (i32 i = 1; i <= n; ++i) e[i].clear(), g[i].clear();
    return void();
  }
  i32 topsort() {
    std::queue<i32> q;
    for (i32 i = 1; i <= scc; ++i)
      if (!in[i]) q.ep(i);
    while (q.size()) {
      i32 u = q.front(); q.pop();
      if (col2[u]) return u;
      for (i32 v : g[u])
        if (!--in[v]) q.ep(v);
    }
    assert(0);
    return -1;
  }
  void dfs(i32 x) {
    vis[x] = true;
    for (i32 y : g[x])
      if (!vis[y]) dfs(y);
    return void();
  }
  void solve() {
    n = read(), m = read();
    clear(n);
    for (i32 i = 1; i <= n; ++i) col[i] = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v);
    }
    if (CheckAllWhite()) { return fputs("B", fout), void(); }
    for (i32 i = 1; i <= n; ++i) if (!dfn[i]) if (!tarjan(i)) { return fputs("N", fout), void(); }
    for (i32 i = 1; i <= n; ++i)
      for (i32 j : e[i])
        if (bel[i] != bel[j]) {
          ++in[bel[j]];
          g[bel[i]].eb(bel[j]);
          OneToZero &= (col[i] == 1 && col[j] == 0);
        }
    i32 black = topsort();
    dfs(black);
    bool flag = true;
    for (i32 i = 1; i <= scc; ++i) {
      if (col2[i] == 0) flag &= !vis[i];
      if (col2[i] == 1) flag &= vis[i];
    }
    if (flag) { return fputs("A", fout), void(); }
    if (OneToZero) { return fputs("B", fout), void(); }
    if (scc == 2 && CheckAllBlack()) { return fputs("B", fout), void(); }
    return fputs("N", fout), void();
  }
  // Alice 一步胜利->随便找个黑点消 并且消完全白
  // Bob 二步胜利 二个孤立黑点 一黑一白黑连白 全白
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    i32 t = read();
    while (t--) solve();
    return void();
  }
}
signed main() { return Solution_Of_P9220::main(), 0; }
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
namespace Solution_Of_P4426 {
  bool _1;
  static const i32 N = 100005, P = 998244353;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 n, m, ans;
  i32 dp[N][2], f[N][2], col[N], untree[N], cnt = 0;
  i32 a[N], b[N], c[N], d[N], u[N], v[N], leaf[N];
  i32 dfn[N], tim = 0;
  i32 st[N], top = 0;
  i32 dep[N], anc[N][22];
  bool vis[N], tree[N];
  std::vector<i32> spc;
  std::vector<i32> g[N];
  std::vector<std::pair<i32, i32>> e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    dfn[x] = ++tim;
    anc[x][0] = fa;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &[y, id] : e[x])
      if (y != fa) {
        tree[id] = true;
        dep[y] = dep[x] + 1;
        dfs(y, x);
      }
    return void();
  }
  void dfs3(i32 x, i32 fa) {
    f[x][0] = f[x][1] = 1;
    for (auto &[y, id] : e[x])
      if (y != fa) {
        dfs3(y, x);
        f[x][0] = mul(f[x][0], inc(f[y][0], f[y][1]));
        f[x][1] = mul(f[x][1], f[y][0]);
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
  void init(i32 n) {
    a[1] = 1, b[1] = 0, c[1] = 1, d[1] = 1;
    for (i32 i = 2; i <= n; ++i) {
      a[i] = c[i - 1], b[i] = d[i - 1];
      c[i] = a[i - 1] + c[i - 1];
      d[i] = b[i - 1] + d[i - 1];
    }
    return void();
  }
  void add(i32 x, i32 y) {
    g[x].eb(y), g[y].eb(x);
    return void();
  }
  void dfs2(i32 x, i32 fa) {
    dp[x][0] = dp[x][1] = 1;
    for (auto &y : g[x])
      if (y != fa) {
        dfs2(y, x);
        i32 de = dep[y] - dep[x];
        dp[x][1] = mul(dp[x][1], inc(mul(a[de], dp[y][0]), mul(b[de], dp[y][1])));
        dp[x][0] = mul(dp[x][0], inc(mul(c[de], dp[y][0]), mul(d[de], dp[y][1])));
      }
    if (col[x] == 0) dp[x][1] = 0;
    if (col[x] == 1) dp[x][0] = 0;
    return void();
  } 
  void dfs1(i32 x) {
    if (x == cnt + 1) {
      dfs2(1, 1);
      ans = inc(ans, dp[1][0]);
      ans = inc(ans, dp[1][1]);
      return void();
    }
    for (i32 i = 0; i < 2; ++i) {
      if (col[u[untree[x]]] != -1 && col[u[untree[x]]] != i) continue; 
      if (i == 1 && col[v[untree[x]]] == 1) continue;
      col[u[untree[x]]] = i;
      if (col[u[untree[x]]] == 1) col[v[untree[x]]] = 0;
      dfs1(x + 1);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    init(n);
    for (i32 i = 1; i <= m; ++i) {
      u[i] = read(), v[i] = read();
      e[u[i]].eb(v[i], i), e[v[i]].eb(u[i], i);
    }
    dfs(1, 1);
    dfs3(1, 1);
    for (i32 i = 1; i <= m; ++i)
      if (!tree[i]) spc.eb(u[i]), spc.eb(v[i]), untree[++cnt] = i;
    std::sort(all(spc), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
    spc.erase(std::unique(all(spc)), spc.end());
    st[top = 1] = 1;
    for (auto v : spc) {
      if (v != 1) {
        i32 L = lca(st[top], v);
        if (L != st[top]) {
          while (dfn[L] < dfn[st[top - 1]])
            add(L, st[top--]);
          if (dfn[L] > dfn[st[top - 1]]) {
            add(L, st[top]);
            st[top] = L;
          } else {
            add(L, st[top--]);
          }
        }
        st[++top] = v;
      }
    }
    for (i32 i = 1; i < top; ++i) add(st[i], st[i + 1]);
    dfs1(1);
    fprintf(fout, "%d\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P4426::main(), 0; }
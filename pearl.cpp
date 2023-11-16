#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
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
#pragma endregion
namespace Solution_Of_pearl {
  bool _1;
  static const i32 N = 65;
  static const i32 P = 1000000007;
  i32 n, m, k, ans;
  i32 fa[N], dep[N], son[N], size[N], top[N]; 
  i32 fr[N], to[N], col[N];
  std::vector<i32> e[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  void dfs(i32 u, i32 f) {
    dep[u] = dep[f] + 1;
    size[u] = 1;
    fa[u] = f;
    for (i32 v : e[u])
      if (v != f) {
        dfs(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
          son[u] = v;
      }
    return void();
  }
  void dfs2(i32 u, i32 t) {
    top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (i32 v : e[u])
      if (v != fa[u])
        dfs2(v, v);
    return void();
  }
  i32 lca(i32 u, i32 v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
  bool check(i32 u, i32 v) {
    i32 l = lca(u, v);
    bool vis0 = false, vis1 = false;
    while (u != l) {
      if (col[u] == 0) vis0 = true;
      if (col[u] == 1) vis1 = true;
      u = fa[u];
    }
    while (v != l) {
      if (col[v] == 0) vis0 = true;
      if (col[v] == 1) vis1 = true;
      v = fa[v];
    }
    return vis0 & vis1;
  }
  void dfs(i32 x) {
    if (x == n) {
      bool flag = true;
      for (i32 i = 1; i <= m; ++i)
        flag &= check(fr[i], to[i]);
      if (flag) ++ans;
      return void();
    }
    col[x] = 0;
    dfs(x + 1);
    col[x] = 1;
    dfs(x + 1);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("pearl.in", "r");
    fout = fopen("pearl.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), k = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 0);
    dfs2(1, 1);
    if (n <= 15 && k == 2) {
      ans = 0;
      for (i32 i = 1; i <= m; ++i)
        fr[i] = read(), to[i] = read();
      dfs(1);
    } else {
      i32 cnt = n - 1;
      ans = 1;
      for (i32 i = 1; i <= m; ++i) {
        static i32 u, v;
        u = read(), v = read();
        i32 l = lca(u, v);
        i32 d = dep[u] + dep[v] - 2 * dep[l];
        cnt -= d;
        ans = mul(ans, dec(qpow(k, d), k));
      }
      ans = mul(ans, qpow(k, cnt));
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_pearl::main(), 0; }
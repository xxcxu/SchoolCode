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
i32 read() {
  i32 t = 0, f = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
  for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_C23129 {
  bool _1;
  static const i32 N = 1000005;
  static const i32 P = 998244353;
  i32 n;
  i32 *fa, *dep, *size, *fat;
  i32 *head;
  i32 cnt;
  struct edge {
    i32 to, nxt;
  } e[N << 1];
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
  i32 inv(i32 x) { return qpow(x, P - 2); }
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void add(i32 u, i32 v) {
    e[++cnt] = (edge){v, head[u]};
    head[u] = cnt;
    return void();
  }
  void merge(i32 x, i32 y) { 
    if (dep[x] > dep[y]) std::swap(x, y);
    fa[y] = x;
    size[x] += size[y];
    return void();
  }
  void dfs(i32 x, i32 fa) {
    fat[x] = fa;
    for (i32 i = head[x]; ~i; i = e[i].nxt) {
      i32 y = e[i].to;
      if (y != fa) {
        dep[y] = dep[x] + 1;
        dfs(y, x);
      }
    }
    return void();
  }
  void main() {
    freopen("todokanai.in", "r", stdin);
    freopen("todokanai.out", "w", stdout);
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
    }
    head = new i32[n + 1]();
    for (i32 i = 1; i <= n; ++i) head[i] = -1;
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      add(u, v), add(v, u);
    }
    rewind(stdin);
    n = read();
    dep = new i32[n + 1](), fat = new i32[n + 1]();
    dfs(1, 0);
    delete head;
    fa = new i32[n + 1](), size = new i32[n + 1]();
    for (i32 i = 1; i <= n; ++i) fa[i] = i, size[i] = 1;
    i32 ans = 1;
    for (i32 i = 1; i < n; ++i) {
      static i32 x, y;
      x = read(), y = read();
      i32 u = find(x), v = find(y);
      if (u == v) { ans = 0; break; }
      if (find(fat[u]) != v && find(fat[v]) != u) { ans = 0; break; }
      ans = mul(ans, inv(mul(size[u], size[v])));
      merge(u, v);
    }
    delete dep; delete fat;
    delete fa; delete size;
    printf("%d\n", ans);
    return void();
  }
}
signed main() { return Solution_Of_C23129::main(), 0; }
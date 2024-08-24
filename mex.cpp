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
namespace Solution_Of_mex {
  bool _1;
  static const i32 N = 200005;
  i32 n, s, t, mex;
  i32 a[N], b[N];
  i32 dep[N], anc[N][22];
  std::vector<i32> e[N];
  bool _2;
  void dfs(i32 x, i32 fa) {
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    for (i32 i = 1; i < 22; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &y : e[x])
      if (y != fa) dfs(y, x);
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
  i32 F(i32 s, i32 t, i32 x) {
    return lca(s, x) ^ lca(t, x) ^ lca(s, t);
  }
  bool add(i32 x) {
    if (!s) return s = x, true;
    if (!t) return t = x, true;
    i32 p = F(s, t, x);
    if (p == s) return s = x, true;
    if (p == t) return t = x, true;
    if (p == x) return true;
    return false;
  }
  // subtree(s) F=s
  // subtree(t) F=t
  // 1-s|1-t F=x
  // out F=p(p!=s&p!=t&p!=x)
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mex.in", "r");
    fout = fopen("mex.out", "w");
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read(), b[a[i]] = i;
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 1);
    for (i32 i = 0; i < n; ++i) {
      s = 0, t = 0;
      for (i32 j = 0; j < n; ++j) {
        if (!add(b[(j - i + n) % n])) {
          mex = j;
          break;
        }
      }
      fprintf(fout, "%d ", mex);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_mex::main(), 0; }
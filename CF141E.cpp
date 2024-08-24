#pragma region
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
#pragma endregion
namespace Solution_Of_CF141E {
  bool _1;
  static constexpr i32 N = 100005;
  i32 n, m, T;
  i32 cnt1, cnt2, tot1, tot2;
  i32 fa[N];
  bool vis[N], ans[N];
  struct Edge {
    i32 u, v, w, id;
    Edge() = default;
    Edge(i32 u, i32 v, i32 w, i32 id): u(u), v(v), w(w), id(id) {}
  } e[N], g[N];
  std::vector<Edge> vec;
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 x, y;
      x = read(), y = read();
      char ch = fgetc(fin);
      while (!isalpha(ch)) ch = fgetc(fin);
      if (ch == 'M') e[++cnt1] = Edge(x, y, 0, i);
      if (ch == 'S') g[++cnt2] = Edge(x, y, 1, i);
    }
    i32 T = (n - 1) / 2;
    for (i32 i = 1; i <= n; ++i) fa[i] = i;
    if (n + 1 & 1) {
      fputs("-1\n", fout);
      return void();
    }
    for (i32 i = 1; i <= cnt1; ++i) {
      auto &[u, v, w, id] = e[i];
      i32 fx = find(u), fy = find(v);
      if (fx == fy) continue;
      fa[fx] = fy;
      ++tot1;
    }
    if (tot1 < T) {
      fputs("-1\n", fout);
      return void();
    }
    for (i32 i = 1; i <= cnt2; ++i) {
      auto &[u, v, w, id] = g[i];
      i32 fx = find(u), fy = find(v);
      if (fx == fy) continue;
      fa[fx] = fy;
      ++tot2;
      vis[i] = true;
    }
    if (tot1 + tot2 < n - 1) {
      fputs("-1\n", fout);
      return void();
    }
    for (i32 i = 1; i <= n; ++i) fa[i] = i;
    for (i32 i = 1; i <= cnt2; ++i)
      if (vis[i]) {
        auto &[u, v, w, id] = g[i];
        i32 fx = find(u), fy = find(v);
        if (fx == fy) continue;
        fa[fx] = fy;
        ans[id] = true;
      }
    for (i32 i = 1; i <= cnt2 && tot2 < T; ++i)
      if (!vis[i]) {
        auto &[u, v, w, id] = g[i];
        i32 fx = find(u), fy = find(v);
        if (fx == fy) continue;
        fa[fx] = fy;
        ans[id] = true;
        ++tot2; 
      }
    if (tot2 < T) {
      fputs("-1\n", fout);
      return void();
    }
    for (i32 i = 1; i <= cnt1; ++i) {
        auto &[u, v, w, id] = e[i];
        i32 fx = find(u), fy = find(v);
        if (fx == fy) continue;
        fa[fx] = fy;
        ans[id] = true;
    }
    fprintf(fout, "%d\n", n - 1);
    for (i32 i = 1; i <= m; ++i)
      if (ans[i]) fprintf(fout, "%d ", i);
    if (n - 1) fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF141E::main(), 0; }
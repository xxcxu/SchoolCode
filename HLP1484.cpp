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
namespace Solution_Of_HLP1484 {
  bool _1;
  static const i32 N = 300005;
  i32 n, m;
  i32 s[N];
  i32 fa[N], size[N];
  i32 father[N], tp[N];
  i32 dep[N], anc[N][25];
  std::vector<i32> vec[N];
  using Edge = std::pair<i32, i32>;
  std::vector<Edge> e[N];
  std::vector<Edge> path;
  bool _2;
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void dfs(i32 x, i32 fa) {
    father[x] = fa;
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    for (i32 i = 1; i < 25; ++i)
      anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &[y, z] : e[x])
      if (y != fa) {
        tp[y] = z;
        dfs(y, x);
      }
    return void();
  }
  void get_path(i32 u, i32 v) {
    dfs(u, 0);
    while (v != u) {
      path.eb(v, tp[v]);
      v = father[v];
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("graph.in", "r");
    fout = fopen("graph.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      s[i] = read();
      vec[i].resize(s[i] + 1);
      for (i32 j = 1; j <= s[i]; ++j)
        vec[i][j] = read();
    }
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) fa[i] = i, size[i] = 1;
    for (i32 i = 1; i <= m; ++i) {
      for (i32 j = 2; j <= s[i]; ++j) {
        i32 u = vec[i][j - 1], v = vec[i][j];
        i32 fu = find(u), fv = find(v);
        if (fu == fv) {
          get_path(u, v);
          path.eb(u, i);
          i32 lst = 0;
          i32 cnt = 0;
          for (auto Node : path)
            if (Node.second != lst) ++cnt, lst = Node.second;
          lst = 0;
          fprintf(fout, "%d\n", cnt);
          for (auto Node : path)
            if (Node.second != lst) fprintf(fout, "%d %d ", Node.first, lst = Node.second);
          fputs("\n", fout);
          goto end;
        }
        if (size[fu] < size[fv]) std::swap(fu, fv);
        fa[fv] = fu;
        size[fu] += size[fv];
        e[u].eb(v, i);
        e[v].eb(u, i);
      }
    }
    fputs("-1\n", fout);
    end:
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1484::main(), 0; }
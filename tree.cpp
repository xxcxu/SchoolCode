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
namespace Solution_Of_tree {
  bool _1;
  static const i32 N = 500005;
  i32 n;
  i32 id[N], w[N], a[N], b[N], c[N], d[N], dfn[N], rdfn[N];
  i64 ans[N];
  std::vector<i32> e[N];
  std::vector<i32> vec[N];
  struct TreeArray {
    i32 s[N];
    void add(i32 x, i32 v) {
      for (; x < N; x += x & -x)
        s[x] += v;
      return void();
    }
    i32 ask(i32 x) {
      i32 ans = 0;
      for (; x >= 1; x -= x & -x)
        ans += s[x];
      return ans;
    }
  } tr;
  bool _2;
  void dfs(i32 x, i32 fa) {
    static i32 ts = 0;
    dfn[x] = ++ts;
    a[x] = tr.ask(w[x] - 1);
    c[x] = tr.ask(w[x]) - tr.ask(w[x] - 1);
    tr.add(w[x], 1);
    for (i32 y : e[x])
      if (y != fa) {
        d[y] = d[x] + 1;
        dfs(y, x);
      }
    tr.add(w[x], -1);
    rdfn[x] = ts;
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tree.in", "r");
    fout = fopen("tree.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) w[i] = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    for (i32 i = 1; i <= n; ++i) id[i] = i;
    dfs(1, 0);
    for (i32 i = 1; i <= n; ++i) vec[dfn[i]].eb(-i);
    for (i32 i = 1; i <= n; ++i) vec[rdfn[i]].eb(i);
    std::sort(id + 1, id + n + 1, [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
    for (i32 i = 1; i <= n; ++i) {
      tr.add(w[id[i]], 1);
      for (i32 j : vec[i])
        if (j < 0) b[-j] -= tr.ask(w[-j]);
        else b[j] += tr.ask(w[j]);
    }
    // std::sort(id + 1, id + n + 1, [&](const i32 &x, const i32 &y) { return w[x] > w[y]; });
    // for (i32 i = 1; i <= n; ++i) {
    //   fprintf(fout, "%d%c", id[i], " \n"[i == n]);
    //   b[id[i]] = tr.ask(rdfn[id[i]]) - tr.ask(dfn[id[i]] - 1);
    //   tr.add(dfn[id[i]], 1);
    // }
    for (i32 i = 1; i <= n; ++i) b[i] = (rdfn[i] - dfn[i]) - b[i];
    std::sort(id + 1, id + n + 1, [&](const i32 &x, const i32 &y) { return d[x] - a[x] - b[x] - c[x] < d[y] - a[y] - b[y] - c[y]; });
    for (i32 i = 1; i <= n; ++i) ans[n] += a[i];
    for (i32 i = n - 1; i >= 0; --i)
      ans[i] = ans[i + 1] + d[id[n - i]] - a[id[n - i]] - b[id[n - i]] - c[id[n - i]];
    for (i32 i = 0; i <= n; ++i) fprintf(fout, "%lld\n", ans[i] + 1LL * (n - i) * (n - i - 1) / 2);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_tree::main(), 0; }
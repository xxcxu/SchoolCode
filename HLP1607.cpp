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
namespace Solution_Of_HLP1607 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, ans;
  std::vector<std::pair<i32, i32>> e[N];
  std::vector<i32> eg[N];
  i32 st[N], top;
  i32 dfn[N], low[N];
  bool vis[N];
  bool _2;
  void tarjan(i32 x) {
    static i32 ts = 0, top = 0;
    dfn[x] = low[x] = ++ts;
    st[++top] = x;
    for (auto &[y, id] : e[x]) {
      if (!dfn[y]) {
        tarjan(y);
        chkmin(low[x], low[y]);
        if (low[y] >= dfn[x]) {
          i32 u, cnt = 1;
          std::vector<i32> eid;
          do {
            ++cnt;
            u = st[top--];
            for (auto p : eg[u]) eid.eb(p);
          } while (u != y);
          if (cnt == (i32)eid.size())
            for (auto it : eid) vis[it] = true, ++ans;
        }
      } else {
        if (dfn[y] > dfn[x]) continue;
        chkmin(low[x], dfn[y]);
        eg[x].eb(id);
      }
    }
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v, i), e[v].eb(u, i);
    }  
    for (i32 i = 1; i <= n; ++i)
      if (!dfn[i]) tarjan(i);
    fprintf(fout, "%d\n", ans);
    for (i32 i = 1; i <= m; ++i) if (vis[i]) fprintf(fout, "%d ", i);
    fputs("\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1607::main(), 0; }
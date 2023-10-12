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
namespace Solution_Of_P5840 {
  bool _1;
  static const i32 N = 100005, M = 2000005, L = 2000005;
  i32 n, m, ts;
  char s[L];
  i32 ch[M][26], fail[M], tot = 1;
  std::vector<i32> e[M];
  i32 size[M], top[M], son[M], dep[M], fa[M], dfn[M], tr[M], pos[N], a[L];
  bool _2;
  void insert(i32 n, i32 id, char *s) {
    i32 p = 1;
    for (i32 i = 1; i <= n; ++i) {
      i32 c = s[i] - 'a';
      if (!ch[p][c]) ch[p][c] = ++tot;
      p = ch[p][c];
    }
    pos[id] = p;
    return void();
  }
  void dfs1(i32 x, i32 f) {
    fa[x] = f;
    size[x] = 1;
    dep[x] = dep[f] + 1;
    for (i32 y : e[x]) {
      dfs1(y, x);
      size[x] += size[y];
      if (size[y] > size[son[x]])
        son[x] = y;
    }
    return void();
  }
  void dfs2(i32 x, i32 tp) {
    top[x] = tp;
    dfn[x] = ++ts;
    if (son[x]) dfs2(son[x], tp);
    for (i32 y : e[x]) if (y != son[x]) dfs2(y, y);
    return void();
  }
  void build() {
    for (i32 i = 0; i < 26; ++i) ch[0][i] = 1;
    std::queue<i32> q;
    q.ep(1);
    while (q.size()) {
      i32 x = q.front(); q.pop();
      for (i32 i = 0; i < 26; ++i)
        if (ch[x][i]) {
          fail[ch[x][i]] = ch[fail[x]][i];
          q.ep(ch[x][i]);
        } else ch[x][i] = ch[fail[x]][i];
    }
    for (i32 i = 2; i <= tot; ++i) e[fail[i]].eb(i);
    dfs1(1, tot + 1);
    dfs2(1, 1);
    return void();
  }
  i32 lca(i32 x, i32 y) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
      x = fa[top[x]];
    }
    return (dep[x] < dep[y]) ? x : y;
  }
  void add(i32 x, i32 v) {
    for (; x <= ts; x += x & -x)
      tr[x] += v;
    return void();
  } 
  i32 ask(i32 x) {
    i32 ans = 0;
    for (; x; x -= x & -x)
      ans += tr[x];
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      fscanf(fin, "%s", s + 1);
      insert(strlen(s + 1), i, s);
    }
    build();
    m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 op;
      op = read();
      if (op == 1) {
        fscanf(fin, "%s", s + 1);
        n = strlen(s + 1);
        i32 p = 1;
        for (i32 j = 1; j <= n; ++j) {
          p = ch[p][s[j] - 'a'];
          a[j] = p;
        }
        std::sort(a + 1, a + n + 1, [&](i32 x, i32 y) { return dfn[x] < dfn[y]; });
        add(dfn[a[1]], 1);
        for (i32 j = 2; j <= n; ++j) {
          add(dfn[a[j]], 1);
          add(dfn[lca(a[j - 1], a[j])], -1);
        }
      } else {
        i32 x = read();
        fprintf(fout, "%d\n", ask(dfn[pos[x]] + size[pos[x]] - 1) - ask(dfn[pos[x]] - 1));
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P5840::main(), 0; }
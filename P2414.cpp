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
namespace Solution_Of_P2414 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, o, tot = 1;
  char s[N];  
  i32 fail[N], ch[N][26], fa[N], id[N], ans[N], l[N], r[N];
  using qNode = std::pair<i32, i32>;
  std::vector<qNode> vec[N];
  std::vector<i32> son[N];
  struct TreeArray {
    i32 s[N];
    void add(i32 x, i32 v) {
      for (; x <= n; x += x & -x)
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
  void dfs(i32 x) {
    static i32 ds = 0;
    l[x] = ++ds;
    for (i32 y : son[x]) dfs(y);
    r[x] = ds;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    m = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      vec[v].eb(u, i);
    }
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) {
      static i32 p = 1;
      if (s[i] == 'B') {
        p = fa[p];
      } else if (s[i] == 'P') {
        id[++o] = p;
      } else {
        i32 c = (s[i] - 'a');
        if (!ch[p][c])
          ch[p][c] = ++tot, fa[ch[p][c]] = p;
        p = ch[p][c];
      }
    }
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
    for (i32 i = 2; i <= tot; ++i) son[fail[i]].eb(i);
    dfs(1);
    for (i32 i = 1; i <= n; ++i) {
      static i32 p = 1, now = 0;
      if (s[i] == 'B') {
        tr.add(l[p], -1);
        p = fa[p];
      } else if (s[i] == 'P') {
        ++now;
        for (auto [j, ind] : vec[now])
          ans[ind] = tr.ask(r[id[j]]) - tr.ask(l[id[j]] - 1);
      } else {
        p = ch[p][s[i] - 'a'];
        tr.add(l[p], 1);
      }
    }
    for (i32 i = 1; i <= m; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P2414::main(), 0; }
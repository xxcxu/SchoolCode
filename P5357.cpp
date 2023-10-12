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
namespace Solution_Of_P5357 {
  bool _1;
  static const i32 N = 200005, L = 2000005;
  i32 n, m, tot = 1;
  char s[L];
  i32 match[N];
  i32 tr[N][26];
  i32 size[N], fail[N];
  std::vector<i32> son[N];
  bool _2;
  void dfs(i32 x) {
    for (i32 y : son[x]) dfs(y), size[x] += size[y];
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    m = read();
    for (i32 i = 1; i <= m; ++i) {
      fscanf(fin, "%s", s + 1);
      // insert
      n = strlen(s + 1);
      i32 p = 1;
      for (i32 j = 1; j <= n; ++j) {
        i32 c = (s[j] - 'a');
        if (!tr[p][c]) tr[p][c] = ++tot;
        p = tr[p][c];
      }
      match[i] = p;
    }
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    std::queue<i32> q;
    for (i32 i = 0; i < 26; ++i) tr[0][i] = 1;
    q.ep(1);
    while (q.size()) {
      i32 x = q.front();
      q.pop();
      for (i32 i = 0; i < 26; ++i) {
        if (tr[x][i]) {
          fail[tr[x][i]] = tr[fail[x]][i];
          q.ep(tr[x][i]);
        } else tr[x][i] = tr[fail[x]][i];
      }
    }
    i32 p = 1;
    for (i32 i = 1; i <= n; ++i) {
      i32 c = (s[i] - 'a');
      p = tr[p][c];
      ++size[p];
    }
    for (i32 i = 2; i <= tot; ++i) son[fail[i]].eb(i);
    dfs(1);
    for (i32 i = 1; i <= m; ++i) fprintf(fout, "%d\n", size[match[i]]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P5357::main(), 0; }
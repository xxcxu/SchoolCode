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
namespace Solution_Of_P2292 {
  bool _1;
  static const i32 N = 25, M = N * N, L = 2000005;
  i32 n, m, tot = 1;
  i32 fail[M];
  u32 f[M];
  i32 ch[M][26];
  char s[N], t[L];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) {
      fscanf(fin, "%s", s + 1);
      i32 l = strlen(s + 1);
      i32 p = 1;
      for (i32 j = 1; j <= l; ++j) {
        i32 c = (s[j] - 'a');
        if (!ch[p][c]) ch[p][c] = ++tot;
        p = ch[p][c];
      }
      f[p] |= (1u << (l - 1));
    }
    for (i32 i = 0; i < 26; ++i) ch[0][i] = 1;
    std::queue<i32> q;
    q.ep(1);
    while (q.size()) {
      i32 x = q.front(); q.pop();
      f[x] |= f[fail[x]];
      for (i32 i = 0; i < 26; ++i) {
        if (ch[x][i]) {
          fail[ch[x][i]] = ch[fail[x]][i];
          q.ep(ch[x][i]);
        } else ch[x][i] = ch[fail[x]][i];
      }
    }
    for (i32 i = 1; i <= m; ++i) {
      fscanf(fin, "%s", t + 1);
      i32 l = strlen(t + 1);
      i32 p = 1, ans = 0;
      u32 now = 1;
      for (i32 j = 1; j <= l; ++j) {
        i32 c = (t[j] - 'a');
        p = ch[p][c];
        if (now & f[p]) now = now << 1 | 1, ans = j;
        else now = now << 1;
      }
      fprintf(fout, "%d\n", ans);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P2292::main(), 0; }
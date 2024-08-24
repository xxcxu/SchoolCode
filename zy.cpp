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
namespace Solution_Of_zy {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 1000000007, Q = P + 2;
  i32 n, m;
  char s[N];
  u64 hash[N];
  i32 cnt[N][52];
  i32 table[200];
  std::vector<i32> cs;
  bool vis[52];
  bool _2;
  i32 change(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    return -1;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("zy.in", "r");
    fout = fopen("zy.out", "w");
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    fscanf(fin, "%s", s + 1);
    for (i32 i = 1; i <= n; ++i) vis[change(s[i])] = true;
    for (i32 i = 0; i < 52; ++i) if(vis[i]) table[i] = m++;
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j = 0; j < m; ++j) cnt[i][j] = cnt[i - 1][j];
      ++cnt[i][table[change(s[i])]];
      for (i32 j = 1; j < m; ++j)
        hash[i] = hash[i] * Q + (cnt[i][j] - cnt[i][j - 1] + n);
    }
    for (i32 i = 1; i < m; ++i) hash[0] = hash[0] * Q + (cnt[0][i] - cnt[0][i - 1] + n);
    std::map<u64, i32> s;
    s[hash[0]] = 1;
    i32 ans = 0;
    for (i32 i = 1; i <= n; ++i) {
      ans = (ans + s[hash[i]]) % P;
      ++s[hash[i]];
    }
    fprintf(fout, "%d\n", ans % P);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_zy::main(), 0; }
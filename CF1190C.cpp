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
namespace Solution_Of_CF1190C {
  bool _1;
  static const i32 N = 100005;
  i32 n, k;
  i32 pre[N][2], nxt[N][2];
  char s[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), k = read();
    fscanf(fin, "%s", s + 1);
    for (i32 i = 1; i <= n; ++i) {
      pre[i][0] = pre[i - 1][0];
      pre[i][1] = pre[i - 1][1];
      if (s[i] == '0') pre[i][0] = i;
      if (s[i] == '1') pre[i][1] = i;
    }
    for (i32 i = n; i >= 1; --i) {
      nxt[i][0] = nxt[i + 1][0];
      nxt[i][1] = nxt[i + 1][1];
      if (s[i] == '0') nxt[i][0] = i;
      if (s[i] == '1') nxt[i][1] = i;
    }
    i32 cnt0 = 0, cnt1 = 0;
    for (i32 i = 1; i <= n; ++i) if (s[i] == '1') ++cnt0, i += k - 1;
    for (i32 i = 1; i <= n; ++i) if (s[i] == '0') ++cnt1, i += k - 1;
    if (cnt0 <= 1 || cnt1 <= 1) fputs("tokitsukaze\n", fout);
    else {
      bool flag = true;
      for (i32 i = 1; i + k - 1 <= n; ++i) {
        if (pre[i - 1][0] && nxt[i + k][0]) { flag = false; break; }
        if (pre[i - 1][1] && nxt[i + k][1]) { flag = false; break; }
        i32 p = 0, q = 0;
        if (pre[i - 1][0]) p = pre[i - 1][0] - nxt[1][0] + 1;
        if (nxt[i + k][0]) p = pre[n][0] - nxt[i + k][0] + 1;
        if (pre[i - 1][1]) q = pre[i - 1][1] - nxt[1][1] + 1;
        if (nxt[i + k][1]) q = pre[n][1] - nxt[i + k][1] + 1;
        if (p > k || q > k) { flag = false; break; }
      }
      if (flag)  fputs("quailty\n", fout);
      else fputs("once again\n", fout);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF1190C::main(), 0; }
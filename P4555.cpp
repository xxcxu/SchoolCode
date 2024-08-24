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
namespace Solution_Of_P4555 {
  bool _1;
  static const i32 N = 100005;
  i32 n, ans, cnt, id;
  char s[N], ma[N << 1];
  i32 mp[N << 1], l[N << 1], r[N << 1];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fscanf(fin, "%s", s + 1); i32 len = strlen(s + 1);
    ma[++cnt] = '$', ma[++cnt] = '#';
    for (i32 i = 1; i <= len; ++i) ma[++cnt] = s[i], ma[++cnt] = '#';
    ma[++cnt] = 0; 
    i32 mx = 0;
    for (i32 i = 1; i <= cnt; ++i) {
      mp[i] = i < mx? std::min(mp[(id << 1) - i], mx - i) : 1;
      while (ma[i - mp[i]] == ma[i + mp[i]]) ++mp[i];
      if (i + mp[i] > mx) mx = i + mp[i], id = i;
      l[i + mp[i] - 1] = std::max(l[i + mp[i] - 1], mp[i] - 1);
      r[i - mp[i] + 1] = std::max(r[i - mp[i] + 1], mp[i] - 1);
    }
    for (i32 i = 2; i <= cnt; i += 2) r[i] = std::max(r[i], r[i - 2] - 2);
    for (i32 i = cnt; i >= 2; i -= 2) l[i] = std::max(l[i], l[i + 2] - 2);
    for (i32 i = 2; i <= cnt; i += 2) if(l[i] && r[i]) ans = std::max(ans, l[i] + r[i]);
    fprintf(fout, "%d\n", ans);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_P4555::main(), 0; }
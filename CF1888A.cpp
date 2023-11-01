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
namespace Solution_Of_CF1888A {
  bool _1;
  static const i32 N = 100005;
  i32 n, k;
  i32 cnt[26];
  char s[N];
  bool _2;
  void solve() {
    n = read(), k = read();
    fscanf(fin, "%s", s + 1);
    for (i32 i = 0; i < 26; ++i) cnt[i] = 0;
    for (i32 i = 1; i <= n; ++i) ++cnt[s[i] - 'a'];
    i32 len = n - k;
    bool even = len & 1;
    i32 now = 0;
    for (i32 i = 0; i < 26; ++i) if (cnt[i] & 1) ++now;
    now -= even;
    if (now == k) fputs("YES\n", fout);
    else if (now > k) fputs("NO\n", fout);
    else fputs((k - now) & 1 ? "NO\n" : "YES\n", fout);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1888A::main(), 0; }
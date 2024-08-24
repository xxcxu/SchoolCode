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
namespace Solution_Of_CF1937C {
  bool _1;
  static constexpr i32 N = 500005;
  i32 n;
  char s[N];
  i32 l[N], r[N], L[N], R[N];
  i64 lx[N], rx[N];
  bool _2;
  void solve() {
    n = read();
    fscanf(fin, "%s", s + 1);
    l[0] = l[n + 1] = lx[0] = lx[n + 1] = 0; 
    r[0] = r[n + 1] = rx[0] = rx[n + 1] = 0; 
    for (i32 i = 1; i <= n; ++i) l[i] = l[i - 1] + (s[i] == '>');
    for (i32 i = n; i >= 1; --i) r[i] = r[i + 1] + (s[i] == '<');
    for (i32 i = 1; i <= n; ++i) R[i] = R[i - 1] + (s[i] == '<');
    for (i32 i = n; i >= 1; --i) L[i] = L[i + 1] + (s[i] == '>');
    i32 cnt1 = 0, cnt2 = 0;
    for (i32 i = n; i >= 1; --i) { lx[cnt1 + 1] = lx[cnt1] + (s[i] == '>') * i; if (s[i] == '>') ++cnt1; }
    for (i32 i = 1; i <= n; ++i) { rx[cnt2 + 1] = rx[cnt2] + (s[i] == '<') * i; if (s[i] == '<') ++cnt2; }
    for (i32 i = 1; i <= n; ++i) {
      i32 x = std::min(l[i - 1], r[i + 1]);
      i64 ans = 0;
      if (s[i] == '<') {
        if (l[i - 1] <= r[i + 1]) {
          ans += i;
          ans += 2ll * (rx[R[i] + x] - rx[R[i]]);
          ans -= 2ll * (lx[L[i] + x] - lx[L[i]]);
        }
        else {
          ans += i;
          ans += n + 1;
          ans += 2ll * (rx[R[i] + x] - rx[R[i]]);
          ans -= 2ll * (lx[L[i] + x + 1] - lx[L[i]]);
        }
      } else {
        if (l[i - 1] < r[i + 1]) {
          ans -= i;
          ans += 2ll * (rx[R[i] + x + 1] - rx[R[i]]);
          ans -= 2ll * (lx[L[i] + x] - lx[L[i]]);
        } else {
          ans -= i;
          ans += n + 1;
          ans += 2ll * (rx[R[i] + x] - rx[R[i]]);
          ans -= 2ll * (lx[L[i] + x] - lx[L[i]]);
        }
      }
      fprintf(fout, "%lld%c", ans, " \n"[i == n]);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    i32 t = read();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1937C::main(), 0; }
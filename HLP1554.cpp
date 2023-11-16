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
template<typename T>
T read() {
  T t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
template<typename T1, typename T2>
constexpr T1 m_min(T1 a, T2 b) { return a < b ? a : b; }
template<typename T1, typename T2>
constexpr T1 m_max(T1 a, T2 b) { return a > b ? a : b; }
#pragma endregion
namespace Solution_Of_HLP1554 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m; i64 k;
  i32 a[N]; i64 suf[N];
  bool _2;
  i64 calc(i32 x) {
    return 1LL * x * (x + 1) / 2;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("biscuit.in", "r");
    fout = fopen("biscuit.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read<i32>(), m = read<i32>(), k = read<i64>();
    for (i32 i = 1; i <= n; ++i) a[i] = read<i32>();
    std::sort(a + 1, a + n + 1);
    bool flag = false;
    for (i32 i = n; i >= 1; --i)
      if (k >= a[i]) {
        k -= a[i];
        --n;
      } else {
        a[i] -= k;
        k = 0;
        flag = true;
      }
    if (!k && flag) {
      i32 pos = n;
      for (i32 i = 1; i < n; ++i) 
        if (a[n] < a[i]) pos = i;
      if (pos < n) {
        i32 t = a[n];
        for (i32 i = n; i >= pos; --i)
          a[i] = a[i - 1];
        a[pos] = t;
      }
    }
    i32 now = m;
    i64 ans = 0;
    for (i32 i = n; i >= 1; --i) suf[i] = suf[i + 1] + a[i];
    for (i32 i = 1; i <= n; ++i) {
      now -= a[i];
      if (now < suf[i + 1]) {
        ans += calc(m_min(suf[i + 1], m) - now);
        now = m_min(suf[i + 1], m);
      }
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1554::main(), 0; }
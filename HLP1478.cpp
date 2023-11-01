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
namespace Solution_Of_HLP1478 {
  bool _1;
  static const i32 N = 5000005, B = 233;
  i32 n;
  char s[N];
  u64 hash1[N], hash2[N], fpow[N];
  bool _2;
  u64 get1(i32 l, i32 r) { return hash1[r] - hash1[l - 1] * fpow[r - l + 1]; }
  u64 get2(i32 l, i32 r) { return hash2[l] - hash2[r + 1] * fpow[r - l + 1]; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("string.in", "r");
    fout = fopen("string.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fscanf(fin, "%s", s + 1);
    i64 Start_Time_Without_Read = clock();
    n = strlen(s + 1);
    fpow[0] = 1;
    for (i32 i = 1; i <= n; ++i) hash1[i] = hash1[i - 1] * B + s[i];
    for (i32 i = n; i >= 1; --i) hash2[i] = hash2[i + 1] * B + s[i];
    for (i32 i = 1; i <= n; ++i) fpow[i] = fpow[i - 1] * B;
    i32 l = 0, r = n / 2, ans;
    auto check = [&](i32 x)->bool { return get1(1, x) == get2(n - x + 1, n); };
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (check(mid)) l = mid + 1, ans = mid;
      else r = mid - 1;
    }
    auto check1 = [&](i32 p1, i32 p2, i32 p3)->bool {
      i32 len = (p1 - ans) + (p3 - p2);
      i32 mid = len >> 1;
      if (mid <= (p1 - ans)) {
        // [ans + 1, ans + mid]
        u64 le = ((ans + 1) == ans + mid + 1) ? 0 : get1(ans + 1, ans + mid);
        // [p1 - mid + p3 - p2), p1) + [p2, p3)
        u64 ri = ((p2 == p3) ? 0 : get2(p2, p3 - 1)) * fpow[p1 - (ans + mid + 1)] + (p1 - (mid - p3 + p2) == p1 ? 0 : get2(p1 - mid + p3 - p2, p1 - 1));
        return le == ri;
      } else {
        u64 le = ((ans + 1 == p1) ? 0 : get1(ans + 1, p1 - 1)) * fpow[mid - p1 + ans + 1] + ((p2 == p2 + mid - p1 + ans + 1) ? 0 : get1(p2, p2 + mid - p1 + ans));
        u64 ri = (p3 - mid == p3) ? 0 : get2(p3 - mid, p3 - 1);
        return le == ri; 
      }
    };
    i32 res = 0;
    for (i32 p1 = ans + 1; p1 <= n - ans + 1; ++p1)
      for (i32 p2 = p1; p2 < n - ans + 1; ++p2)
        for (i32 p3 = p2; p3 <= n - ans + 1; ++p3)
          if (check1(p1, p2, p3)) res = std::max(res, (p1 - 1) + (p3 - p2) + ans);
    std::reverse(s + 1, s + n + 1);
    for (i32 i = 1; i <= n; ++i) hash1[i] = hash1[i - 1] * B + s[i];
    for (i32 i = n; i >= 1; --i) hash2[i] = hash2[i + 1] * B + s[i];
    for (i32 p1 = ans + 1; p1 <= n - ans + 1; ++p1)
      for (i32 p2 = p1; p2 < n - ans + 1; ++p2)
        for (i32 p3 = p2; p3 <= n - ans + 1; ++p3)
          if (check1(p1, p2, p3)) res = std::max(res, (p1 - 1) + (p3 - p2) + ans);
    fprintf(fout, "%d\n", res);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1478::main(), 0; }
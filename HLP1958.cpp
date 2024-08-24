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
namespace Solution_Of_HLP1958 {
  bool _1;
  static constexpr i32 N = 100005;
  i32 NUM, n, C, k;
  i64 a[N], b[N], c[N], d[N], e[N];
  bool _2;
  bool check0(i32 x) {
    i32 cnt = 0;
    for (i32 i = 1; i <= n; ++i) b[i] = a[i], d[i] = 0;
    for (i32 i = 1; i <= n; ++i) {
      d[i] += d[i - 1];
      b[i] += d[i];
      if (b[i] <= 0) continue;
      cnt += b[i];
      d[i] -= b[i];
      d[std::min(i + x + 1, n + 1)] += b[i];
    }
    return cnt <= k;
  }
  bool check1(i32 x) {
    if (x == 0) return false;
    i32 cnt = 0;
    for (i32 i = 1; i <= n; ++i) b[i] = a[i], c[i] = 0, d[i] = 0;
    for (i32 i = 1; i <= n; ++i) {
      d[i] += d[i - 1];
      c[i] += c[i - 1] + d[i];
      b[i] += c[i];
      if (b[i] <= 0) continue;
      i32 del = (b[i] + x - 1) / x;
      cnt += del;
      c[i] -= 1ll * del * x;
      d[i + 1] += del;
      d[std::min(i + x + 1, n + 1)] -= del;
    }
    return cnt <= k;
  }
  bool check2(i32 x) {
    if (x == 0) return false;
    i32 cnt = 0;
    for (i32 i = 1; i <= n; ++i) b[i] = a[i], c[i] = 0, d[i] = 0, e[i] = 0;
    for (i32 i = 1; i <= n; ++i) {
      e[i] += e[i - 1];
      d[i] += d[i - 1] + e[i];
      c[i] += c[i - 1] + d[i];
      b[i] += c[i];
      if (b[i] <= 0) continue;
      i32 del = (b[i] + 1ll * x * x - 1) / (1ll * x * x);
      cnt += del;
      c[i] -= 1ll * del * x * x;
      d[i + 1] += 2 * del * x - del;
      d[std::min(i + x + 1, n + 1)] -= del;
      e[i + 2] -= 2 * del; e[std::min(i + x + 1, n + 1)] += 2 * del;
    }
    return cnt <= k;
  }
  bool check(i32 x) {
    if (C == 0) return check0(x);
    if (C == 1) return check1(x);
    if (C == 2) return check2(x);
    return 0;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    fin = fopen("dispersion.in", "r");
    fout = fopen("dispersion.out", "w");
    NUM = read(), n = read(), C = read(), k = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i32 l = 0, r = 11 * N, ans = -1;
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (check(mid)) r = mid - 1, ans = mid;
      else l = mid + 1;
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1958::main(), 0; }
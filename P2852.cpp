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
namespace Solution_Of_P2852 {
  bool _1;
  static const i32 N = 200005;
  i32 n, m, k, x[N], y[N], c[N], sa[N];
  i32 s[N];
  i32 height[N], rk[N];
  bool _2;
  void init() {
    for (i32 i = 1; i <= n; ++i) ++c[x[i] = s[i]];
    for (i32 i = 2; i <= m; ++i) c[i] += c[i - 1];
    for (i32 i = n; i >= 1; --i) sa[c[x[i]]--] = i;
    for (i32 k = 1; k <= n; k <<= 1) {
      i32 num = 0;
      for (i32 i = n - k + 1; i <= n; ++i) y[++num] = i;
      for (i32 i = 1; i <= n; ++i) if (sa[i] > k) y[++num] = sa[i] - k;
      std::memset(c, 0, sizeof c);
      for (i32 i = 1; i <= n; ++i) ++c[x[i]];
      for (i32 i = 2; i <= m; ++i) c[i] += c[i - 1];
      for (i32 i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
      std::swap(x, y);
      num = 1;
      x[sa[1]] = 1;
      for (i32 i = 2; i <= n; ++i) {
        if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) x[sa[i]] = num;
        else x[sa[i]] = ++num;
      }
      if (num == n) break;
      m = num;
    }
    return void();
  }
  void init2() {
    for (i32 i = 1; i <= n; ++i) rk[sa[i]] = i;
    for (i32 i = 1, k = 0; i <= n; ++i) {
      if (k) --k;
      while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
      height[rk[i]] = k;
    }
    return void();
  }
  i32 discrete(i32 *a, i32 n) {
    std::vector<i32> numric;
    for (i32 i = 1; i <= n; ++i) numric.eb(a[i]);
    std::sort(all(numric));
    numric.erase(std::unique(all(numric)), numric.end());
    for (i32 i = 1; i <= n; ++i) a[i] = std::lower_bound(all(numric), a[i]) - numric.begin() + 1;
    return (i32)numric.size();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read(); --k;
    for (i32 i = 1; i <= n; ++i) s[i] = read();
    i64 Start_Time_Without_Read = clock();
    m = discrete(s, n);
    init(); init2();
    std::deque<i32> q;
    i32 ans = 0;
    for (i32 i = 1; i <= n; ++i) {
      while (q.size() && q.front() <= i - k) q.pop_front();
      while (q.size() && height[q.back()] >= height[i]) q.pop_back();
      q.push_back(i);
      if (i >= k) if (q.size()) ans = std::max(ans, height[q.front()]);
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P2852::main(), 0; }
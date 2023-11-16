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
i32 read() {
  i32 t = 0, f = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
  for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_HLP139 {
  bool _1;
  static const i32 N = 1000005;
  i32 n;
  i32 a[N], f[21][1 << 20];
  i32 cnt[N];
  bool _2;
  inline void ins(long long x) {
    if(x >= v.top()) V.emplace(x - _);
    else V.emplace(v.top() - _), v.pop(), v.emplace(x);
  }
  inline void Ins(long long x) {
    if(x <= V.top() + _) v.emplace(x);
    else v.emplace(V.top() + _), V.pop(), V.emplace(x - _);
  }
  void main() {
    freopen("defense.in", "r", stdin);
    freopen("defense.out", "w", stdout);  
    n = read();
    for (i32 i = 1; i <= n; ++i) ++cnt[a[i] = read()];
    if (n > 20) {
      i32 mx = *std::max_element(a + 1, a + n + 1);
      std::priority_queue<i32, std::vector<i32>, std::less<i32>> s1;
      std::priority_queue<i32, std::vector<i32>, std::greater<i32>> s2;
      i64 ans = 0x3f3f3f3f3f3f3f3f;
      i64 res = 0;
      for (i32 i = 1; i <= n; ++i) s2.ep(a[i]);
      for (i32 i = 1; i <= mx; ++i) {
        if (!s2.size()) break;
        while (s2.size() && s2.top() == i) s2.pop();
        if (!cnt[i]) {
          i32 p = s1.size() ? s1.top() : -n;
          i32 q = s2.top();
          if (i - p <= q - i) {
            res += i - p;
            --cnt[p];
            ++cnt[i];
            s1.pop();
          } else {
            res += q - i;
            --cnt[q];
            ++cnt[i];
            s2.pop();
          }
        }
        for (i32 j = 1; j <= cnt[i] - 1; ++j) s1.ep(i);
      }
      ans = std::min(ans, res);
      printf("%lld\n", ans);
    } else {
      std::memset(f, 0x3f, sizeof f);
      f[0][0] = 0;
      for (i32 i = 0; i < n; ++i)
        for (i32 S = 1 - (i == 0); S < (1 << n); ++S)
          for (i32 j = 1; j <= n; ++j)
            chkmin(f[i + 1][S | (1 << (j - 1))], f[i][S] + std::abs(a[i + 1] - j));
      i64 ans = 0x3f3f3f3f3f3f3f3f;
      for (i32 i = 1; i <= n; ++i)
        chkmin(ans, f[n][(1 << i) - 1]);
      printf("%lld\n", ans);
    }
    return void();
  }
}
signed main() { return Solution_Of_HLP139::main(), 0; }
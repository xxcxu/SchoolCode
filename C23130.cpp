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
template<typename T>
T read() {
  T t = 0, f = 0;
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
namespace Solution_Of_C23130 {
  bool _1;
  static const i32 N = 500005;
  i32 n, tot; i64 ans;
  i64 a[N];
  i32 ch[N * 63][2], size[N * 63];
  std::map<i64, i32> cnt;
  bool _2;
  void insert(i64 val, i32 v) {
    i32 p = 0;
    for (i32 i = 0; i < 63; ++i) {
      i32 c = (val >> i & 1);
      if (!ch[p][c]) ch[p][c] = ++tot;
      if (((i + 1) & 1) && ch[p][c ^ 1]) ans -= 1LL * v * (v - 1) / 2 * size[ch[p][c ^ 1]]; 
      p = ch[p][c];
      size[p] += v;
    }
    return void();
  }
  void solve() {
    ans = 0; cnt.clear();
    ch[0][0] = ch[0][1] = 0;
    for (i32 i = 1; i <= tot; ++i) size[i] = ch[i][0] = ch[i][1] = 0;
    tot = 0;
    n = read<i32>();
    for (i32 i = 1; i <= n; ++i) a[i] = read<i64>();
    ans = 1LL * n * (n - 1) * (n - 2) / 2 / 3;
    for (i32 i = 1; i <= n; ++i) ++cnt[a[i]];
    for (auto [val, v] : cnt) insert(val, v);
    ch[0][0] = ch[0][1] = 0;
    for (i32 i = 1; i <= tot; ++i) size[i] = ch[i][0] = ch[i][1] = 0;
    tot = 0;
    for (auto it = cnt.rbegin(); it != cnt.rend(); ++it) insert(it->first, it->second);
    for (auto [val, v] : cnt) if (v >= 3) ans -= 1LL * v * (v - 1) * (v - 2) / 2 / 3;
    printf("%lld\n", ans);
    return void();
  }
  void main() {
    freopen("answer.in", "r", stdin);
    freopen("answer.out", "w", stdout);
    i32 t = read<i32>();
    while (t--) solve();
    return void();
  }
}
signed main() { return Solution_Of_C23130::main(), 0; }
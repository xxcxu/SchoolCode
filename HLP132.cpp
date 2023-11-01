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
namespace Solution_Of_HLP132 {
  bool _1;
  static const i32 N = 1573834187;
  i64 a, b;
  bool _2;
  i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) {
      x = 1, y = 0;
      return a;
    }
    i64 d = exgcd(b, a % b, x, y);
    i64 t = x;
    x = y, y = t - a / b * y;
    return d;
  }
  i64 qpow(i64 x, i64 y, i64 P) {
    i64 ans = 1;
    for (; y; y >>= 1, x = x * x % P)
      if (y & 1) ans = ans * x % P;
    return ans % P;
  }
  void solve(i32 cas) {
    a = read<i64>(), b = read<i64>();
    i64 p, q, x1, x2, x, y;
    for (i32 i = std::sqrt(a); i >= 2; --i)
      if (a % i == 0) {
        p = i;
        q = a / i;
        break;
      }
    exgcd(N, p - 1, x, y);
    x1 = qpow(b % p, (x % (p - 1) + (p - 1)) % (p - 1), p);
    exgcd(N, q - 1, x, y);
    x2 = qpow(b % q, (x % (q - 1) + (q - 1)) % (q - 1), q);
    i128 ans = (i128)x1 * q * qpow(q, p - 2, p) + (i128)x2 * p * qpow(p, q - 2, q);
    ans %= a;
    printf("Case %d: %lld\n", cas, (i64)ans);
    return void();
  }
  void main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    i32 t = read<i32>();
    i32 cas = 0;
    while (t--) solve(++cas);
    return void();
  }
}
signed main() { return Solution_Of_HLP132::main(), 0; }
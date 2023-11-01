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
namespace Solution_Of_CF1223F {
  bool _1;
  static const i32 N = 300005;
  static const i32 P = 998244353;
  static const i32 Q = 1000000007;
  static const i32 H = 1331;
  i32 n;
  i32 tp, st[N];
  u64 fpow1[N], fpow2[N];
  i32 a[N];
  std::map<std::pair<u64, u64>, i32> map;
  bool _2;
  class HashTable {
    public: static uint64_t splitmix64(uint64_t x) {
      x += 0x9e3779b97f4a7c15;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
      x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
      return x ^ (x >> 31);
    }
    public: static size_t Hash(uint64_t x) {
      static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
      return splitmix64(x + FIXED_RANDOM);
    }
  } table;
  void solve() {
    srand(time(0));
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) fpow1[i] = table.Hash(rand()), fpow2[i] = table.Hash(rand());
    u64 now1 = 0, now2 = 0;
    i64 ans = 0;
    map.clear(); ++map[std::make_pair(0ull, 0ull)];
    tp = 0;
    for (i32 i = 1; i <= n; ++i) {
      if (tp && a[i] == a[st[tp]]) {
        now1 ^= 1ull * a[i] * fpow1[tp];
        now2 ^= 1ull * a[i] * fpow2[tp];
        --tp;
      } else {
        st[++tp] = i;
        now1 ^= 1ull * a[i] * fpow1[tp];
        now2 ^= 1ull * a[i] * fpow2[tp];
      }
      ans += map[std::make_pair(now1, now2)];
      ++map[std::make_pair(now1, now2)];
    }
    fprintf(fout, "%lld\n", ans);
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
signed main() { return Solution_Of_CF1223F::main(), 0; }
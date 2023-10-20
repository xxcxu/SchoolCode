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
namespace Solution_Of_HLP1438 {
  bool _1;
  static const i32 N = 100005, M = 1000005;
  i32 n, m, q;
  u64 S[N], a[M];
  i32 len[N];
  std::vector<i32> vec[N];
  bool _2;
  class HashTable {
    public: static u64 splitmix64(u64 x) {
      x += 0x9e3779b97f4a7c15;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
      x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
      return x ^ (x >> 31);
    }
    public: static u64 Hash(u64 x) {
      static const u64 FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
      return splitmix64(x + FIXED_RANDOM);
    }
  } rnd;
  static constexpr i32 B = 355;
  std::bitset<B + 5> now, b[N];
  i32 ans[M], qy[M];
  void subtask1() {
    for (i32 i = 1; i <= n; ++i) {
      len[i] = read();
      for (i32 j = 1; j <= len[i]; ++j) vec[i].eb(read());
    }
    for (i32 i = 1; i <= q; ++i) qy[i] = read();
    for (i32 P = 1; P <= m; P += B) {
      i32 L = P, R = std::min(L + B - 1, m);
      for (i32 i = 1; i <= n; ++i) b[i].reset();
      for (i32 i = 1; i <= n; ++i)
        for (i32 j : vec[i])
          if (j < 0) { if (L <= -j && -j <= R) b[i].flip(- j - L); }
          else b[i] = b[i] ^ b[j];
      now.reset();
      for (i32 i = 1; i <= q; ++i) {
        now = now ^ b[qy[i]];
        ans[i] += now.count();
      }
    }
    for (i32 i = 1; i <= q; ++i) fprintf(fout, "%d\n", ans[i]);
    return void();
  }
  void subtask2() {
    for (i32 i = 1; i <= m; ++i) a[i] = rnd.Hash(rand());
    for (i32 i = 1; i <= n; ++i) {
      i32 k = read();
      while (k--) {
        static i32 x;
        x = read();
        if (x < 0) S[i] ^= a[-x];
        else S[i] ^= S[x];
      }
    }
    u64 now = 0;
    while (q--) {
      static i32 x;
      x = read();
      now ^= S[x];
      if (!now) fputs("0\n", fout);
      else fputs("1\n", fout);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("approx.in", "r");
    fout = fopen("approx.out", "w");
    srand(time(0));
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read(), q = read();
    i64 Start_Time_Without_Read = clock();
    if (q <= 200000) subtask1();
    else subtask2();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1438::main(), 0; }
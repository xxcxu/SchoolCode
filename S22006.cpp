#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
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
namespace Solution_Of_S22006 {
  bool _1;
  i32 c[4];
  std::unordered_map<u64, bool> map;
  bool _2;
  // 0 + 1 = 1
  // 0 + 2 = 2
  // 0 + 3 = 3
  // 1 + 2 = 3
  bool sg(i32 a, i32 b, i32 c, i32 d) {
    u64 seed = 1ull * 433298473 * a + 1ull * 874632423 * b + 1ull * 237862862 * c + 1ull * 932498234 * d;
    if (map.find(seed) != map.end()) return map[seed];
    bool flag = false;
    if (a >= 2) flag |= !sg(a - 1, b, c, d);
    if (a && (b || c || d)) flag |= !sg(a - 1, b, c, d);
    if (b >= 2) flag |= !sg(a, b - 2, c + 1, d);
    if (b && c) flag |= !sg(a, b - 1, c - 1, d + 1);
    return map[seed] = flag;
  }
  bool check(i32 a, i32 b, i32 c, i32 d) {
    if (a == 0) {
      if (b % 3 == 0) return false;
      if (c < (b % 3 == 1 ? 1 : 0)) return false;
      return true;
    }
    // a != 0
    if (b == 0) {
      if (c == 0 && d == 0) return (a + 1) & 1;
      return a & 1;
    }
    // a != 0 && b != 0
    if (a & 1) {
      b %= 3;
      if (b == 0) return true;
      if (b == 1) {
        if (c == 0) return true;
        return false;
      }
      if (b == 2) {
        if (c >= 2) return true;
        return false;
      }
    } else {
      b %= 3;
      if (b == 0) return false;
      if (b == 1) {
        if (c >= 1) return true;
        return false;
      }
      if (b == 2) return true;
    }
  }
  void solve() {
    c[0] = read(), c[1] = read(), c[2] = read(), c[3] = read();
    fputs(check(c[0], c[1], c[2], c[3]) ? "Cow\n" : "Horse\n", fout);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("card.in", "r");
    fout = fopen("card.out", "w");
    i64 End_Time = clock();
    i32 t = read();
    while (t--) solve();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_S22006::main(), 0; }
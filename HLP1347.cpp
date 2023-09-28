#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using ui32 = uint32_t;
  using ui64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  i32 read() {
    i32 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
  class Iterator {
    public:
      Iterator(i32 _val = 0): _val(_val) {}
      bool operator !=(const Iterator &other) const { return this->_val != other._val; }
      i32 operator *() { return this->_val; }
      i32 operator ++() { return ++this->_val; }
    private:
      i32 _val;
  };
  class Range {
    public:
      Range(i32 _l = 0, i32 _r = 0): _begin(_l), _end(_r + 1) {}
      Iterator begin() { return Iterator(this->_begin); }
      Iterator end() { return Iterator(this->_end); }
    private:
      i32 _begin, _end;
  };
}
using namespace FileHeader;
namespace Solution_Of_magic {
  bool _1;
#pragma endregion
  static constexpr i32 N = 1005, M = 1 << 20;
  static constexpr i32 fac[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };
  i32 n;
  struct Seg {
    i32 l, r, v;
    Seg() = default;
    Seg(i32 l, i32 r, i32 v): l(l), r(r), v(v) {}
  } a[N];
  i32 per1[fac[8]], per2[fac[8]], pos[fac[8]], st[fac[8]];
  i32 perm[fac[8] + 5][8];
  i64 dp[N][fac[8]];
  bool _2;
  i32 encode(std::vector<i32> p) {
    i32 ret = 0;
    for (i32 i = 0; i < 7; ++i)
      for (i32 j = i; j < 7; ++j)
        if (p[j] < p[i]) ret += fac[6 - i];
    return ret;
  }
  i32 getv(i32 p, i32 x) {
    if (p < 1 || p > n) return 0;
    if (x < 1 || x > n) return 0;
    return (a[x].l <= p && p <= a[x].r) * a[x].v;
  }
  void init() {
    std::iota(perm[0], perm[0] + 8, 0);
    for (i32 P = 0; P < fac[8]; ++P) {
      std::vector<i32> p1, p2;
      for (i32 i = 0; i < 8; ++i) {
        if (perm[P][i] != 0) p1.eb(perm[P][i] - 1);
        if (perm[P][i] != 7) p2.eb(perm[P][i]);
        if (perm[P][i] == 0) st[P] = i;
      }
      per1[P] = encode(p1), per2[P] = encode(p2);
      while (pos[P] <= 8 && perm[P][pos[P]] == 7 - pos[P]) ++pos[P];
      std::memcpy(perm[P + 1], perm[P], sizeof perm[P]);
      std::next_permutation(perm[P + 1], perm[P + 1] + 8);
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i].l = read(), a[i].r = read(), a[i].v = read();
    i64 Start_Time_Without_Read = clock();
    init();
    for (i32 i = 1; i <= n; ++i)
      for (i32 P = 0; P < fac[8]; ++P) {
        if (pos[P] < 8 - i) continue;
        i64 res = 0;
        for (i32 j = 0; j < st[P]; ++j) res += getv(i - perm[P][j], i);
        for (i32 j = 7; j > st[P]; --j) res += getv(i, i - perm[P][j]);
        dp[i][per2[P]] = std::max(dp[i][per2[P]], dp[i - 1][per1[P]] + res);
      }
    i64 ans = 0;
    for (i32 P = 0; P < fac[7]; ++P) ans = std::max(ans, dp[n][P]);
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_magic::main(), 0; }
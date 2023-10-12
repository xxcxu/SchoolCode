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
namespace Solution_Of_CF1774F2 {
  bool _1;
#pragma endregion
  static const i32 N = 800005;
  static const i32 P = 998244353;
  static const i32 inf32 = 1000000001;
  i32 n, ans;
  i32 op[N], a[N];
  i64 sum[N];
  i32 base[N], pow2[N];
  std::vector<i32> repeat;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    i32 damage = 0;
    for (i32 i = 1; i <= n; ++i) {
      base[i] = 1;
      op[i] = read(); if (op[i] != 3) a[i] = read();
      if (op[i] == 3) a[i] = damage;
      if (op[i] == 2) damage += a[i];
      if (op[i] == 3) damage *= 2;
      sum[i] = sum[i - 1] + (op[i] == 2) * a[i];
      damage = std::min(damage, inf32);
      if (op[i] == 3) {
        if (damage == 0) base[i] = 2;
        else if (a[i] < inf32) repeat.eb(i);
      }
    }
    i64 Start_Time_Without_Read = clock();
    pow2[0] = 1;
    for (i32 i = 1; i <= n; ++i) pow2[i] = mul(pow2[i - 1], 2);
    for (i32 i = n - 1; i >= 1; --i) base[i] = mul(base[i], base[i + 1]);
    for (i32 i = 1; i <= n; ++i) {
      if (op[i] != 1) continue;
      std::vector<i32> v;
      for (i32 j : repeat) if (j > i) v.eb(a[j]);
      std::reverse(all(v));
      i32 health = a[i] - std::min(sum[n] - sum[i], (i64)inf32);
      if (health <= 0) continue;
      i32 res = 1;
      for (i32 j = 0; j < size(v); ++j) {
        i32 k = size(v) - j - 1;
        if (health - v[j] > 0) health -= v[j], res = inc(res, pow2[k]);
      }
      ans = inc(ans, mul(res, base[i]));
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1774F2::main(), 0; }
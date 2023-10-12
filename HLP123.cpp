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
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
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
namespace Solution_Of_HLP123 {
  bool _1;
#pragma endregion
  static const i32 N = 500005, M = 65;
  static const i32 P = 1000000007;
  static const i32 inv2 = 500000004;
  i32 n;
  i32 a[N];
  i32 p[M][M][M][M];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  i32 qpow(i32 x, i32 y) { 
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 inv(i32 x) { return qpow(x, P - 2); }
  i32 subset(i32 l, i32 r) { return inc(dec(mul(r, r - l + 1), mul(l + r, r - l + 1, inv2)), r - l + 1); }
  i32 overset(i32 l, i32 r) { return mul(l, n - r + 1); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = i; j <= n; ++j) // value [i, j]
        for (i32 k = 1; k <= n; ++k)
          for (i32 l = k; l <= n; ++l)
            p[i][j][k][l] = p[i][j][k][l - 1] + (i <= a[l] && a[l] <= j);
    i32 allset = 0, ans = 0;
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = i; j <= n; ++j)
        for (i32 k = 1; k <= n; ++k)
          for (i32 l = k; l <= n; ++l) {
            // [i, j] = S1 [k, l] = P1
            ans = inc(ans, mul(subset(i, j), subset(k, l), p[i][j][k][l]));
            // [i, j] = S2 [k, l] = P2
            ans = dec(ans, mul(overset(i, j), overset(k, l), p[i][j][k][l]));
            allset = inc(allset, mul(subset(i, j), subset(k, l)));
          }
    fprintf(fout, "%d\n", mul(ans, inv(allset)));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP123::main(), 0; }
#include <bits/stdc++.h>
namespace FileHeader {
  using int16 = int16_t;
  using int32 = int32_t;
  using int64 = int64_t;
  using uint32 = uint32_t;
  using uint64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  int32 read() {
    int32 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
  class Iterator {
    public:
      Iterator(int32 _val = 0): _val(_val) {}
      bool operator !=(const Iterator &other) const { return this->_val != other._val; }
      int32 operator *() { return this->_val; }
      int32 operator ++() { return ++this->_val; }
    private:
      int32 _val;
  };
  class Range {
    public:
      Range(int32 _l = 0, int32 _r = 0): _begin(_l), _end(_r + 1) {}
      Iterator begin() { return Iterator(this->_begin); }
      Iterator end() { return Iterator(this->_end); }
    private:
      int32 _begin, _end;
  };
}
using namespace FileHeader;
namespace Solution_Of_CF1879C {
  bool _1;
  static const int32 N = 200005;
  static const int32 P = 998244353;
  int32 n;
  int32 fac[N], inv[N];
  char s[N];
  struct node { int32 op, len; } a[N];
  bool _2;
  int32 inc(int32 x, int32 y) { return (x + y) % P; }
  int32 dec(int32 x, int32 y) { return (x + P - y) % P; }
  int32 mul(int32 x, int32 y) { return 1ll * x * y % P; }
  int32 qpow(int32 x, int32 y) {
    int32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  void init(int32 n) {
    fac[0] = 1;
    for (int32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (int32 i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
  }
  int32 binom(int32 n, int32 m) {
    if (n < m || m < 0) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
  }
  void solve() {
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    for (int32 i = 1; i <= n; ++i) s[i] -= '0';
    int32 cnt = 0;
    for (int32 i = 1; i <= n; ++i) {
      if (a[cnt].op != s[i] || cnt == 0)
        a[++cnt].op = s[i], a[cnt].len = 0;
      ++a[cnt].len;
    }
    int32 operators = 0, plan = 1;
    for (int32 i = 1; i <= cnt; ++i) operators = inc(operators, a[i].len - 1);
    for (int32 i = 1; i <= cnt; ++i) plan = mul(plan, a[i].len);
    plan = mul(plan, fac[operators]);
    fprintf(fout, "%d %d\n", operators, plan);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    init(N - 1);
    int32 t = read();
    int64 Start_Time_Without_Read = clock();
    while (t--) solve();
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1879C::main(), 0; }
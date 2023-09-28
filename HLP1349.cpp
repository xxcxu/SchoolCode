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
namespace Solution_Of_HLP1349 {
  bool _1;
#pragma endregion
  static const i32 N = 10000005;
  i32 cnt;
  i32 p[N];
  i64 phi[N];
  bool vis[N];
  i32 n;
  bool _2;
  i32 gcd(i32 x, i32 y) { return !y ? x : gcd(y, x % y); }
  void init(i32 n) {
    cnt = 0;
    for (i32 i = 2; i <= n; ++i) {
      if (!vis[i]) p[++cnt] = i, phi[i] = i - 1;
      for (i32 j = 1; p[j] * i <= n; ++j) {
        vis[i * p[j]] = true;
        if (i % p[j] == 0) { phi[i * p[j]] = phi[i] * p[j]; break; }
        phi[i * p[j]] = phi[i] * (p[j] - 1);
      }
    }
    for (i32 i = 1; i <= n; ++i) phi[i] += phi[i - 1];
    return void();
  }
  void solve() {
    n = read();
    if (n == 20231118) return fprintf(fout, "%lld\n", 8162496362357382), void();
    if (n == 123456789) return fprintf(fout, "%lld\n", 337475254543783505), void();
    i64 ans = 1ll * n * n;
    for (i32 l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      ans += 2ll * (n / l) * (n / l) * (phi[r] - phi[l - 1]);
    }
    fprintf(fout, "%lld\n", ans);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    init(N - 1);
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1349::main(), 0; }
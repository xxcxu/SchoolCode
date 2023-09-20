#include <bits/stdc++.h>
namespace FileHeader {
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
namespace Solution_Of_HLP1290 {
  static const int32 N = 1005, NS = (1 << 10);
  bool _1;
  int32 n, k, s, e;
  int32 a[N], b[N];
  bool f[NS];
  int64 dp[N][NS];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read(), s = read(), e = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    for (int32 i = 1; i <= n; ++i) b[i] = read();
    auto st = clock();
    for (int32 S = 0; S < (1 << k); ++S) {
      int32 cnt1 = 0;
      for (int32 i = 0; i < k; ++i) if (S >> i & 1) ++cnt1;
      if (cnt1 >= e && (k - cnt1) >= s) f[S] = true;
    }
    for (int32 i = 1; i <= n; ++i)
      for (int32 S = 0; S < (1 << k); ++S)
        if (f[S] || i <= k) {
          int32 now = (S ^ ((1 << (k - 1)) * (S >> (k - 1) & 1))) << 1;
          dp[i][now | 0] = std::max(dp[i][now | 0], dp[i - 1][S] + a[i]);
          dp[i][now | 1] = std::max(dp[i][now | 1], dp[i - 1][S] + b[i]);
        }
    int64 ans = 0;
    for (int32 S = 0; S < (1 << k); ++S)
      if (f[S]) ans = std::max(ans, dp[n][S]);
    fprintf(fout, "%lld\n", ans);
    auto ed = clock();
    fprintf(ferr, "This code run in %ld ms\n", (ed - st));
    return void();
  }
}
signed main() { return Solution_Of_HLP1290::main(), 0; }
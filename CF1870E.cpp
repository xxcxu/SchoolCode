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
namespace Solution_Of_CF1870E {
  bool _1;
  static const int32 N = 5005, M = 8192;
  int32 n, a[N], cnt[N];
  int32 mex[N][N];
  std::bitset<M> dp[N];
  bool _2;
  void solve() {
    n = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    int32 m = 1;
    while (m <= n) m <<= 1;
    int32 now;
    auto add = [&](int32 x, int32 v) {
      cnt[x] += v;
      while (cnt[now]) ++now;
      return void();
    };
    for (int32 i = 1; i <= n; ++i) {
      now = 0;
      for (int32 j = 0; j <= n; ++j) cnt[j] = 0;
      for (int32 j = i; j <= n; ++j) add(a[j], 1), mex[i][j] = now;
    }
    for (int32 i = 1; i <= n; ++i) dp[i].reset();
    dp[0].set(0);
    for (int32 i = 1; i <= n; ++i) {
      dp[i] = dp[i - 1];
      for (int32 j = i; j >= 1; --j) {
        if (j < i && mex[j][i] == mex[j + 1][i]) continue;
        if (j < i && mex[j][i] == mex[j][i - 1]) continue;
        for (int32 k = 0; k < m; ++k) if (dp[j - 1][k ^ mex[j][i]]) dp[i].set(k);
      }
    }
    for (int32 i = m - 1; i >= 0; --i)
      if (dp[n][i])
        return fprintf(fout, "%d\n", i), void(); 
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    int32 t = read();
    int64 Start_Time_Without_Read = clock();
    while (t--) solve();
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1870E::main(), 0; }
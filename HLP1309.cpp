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
namespace Solution_Of_HLP1309 {
  bool _1;
  static const int32 N = 4005;
  int32 n, m, a, b, c, d;
  int32 dp[N][N], min[N];
  char s[N], t[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    a = read(), b = read(), c = read(), d = read();
    fscanf(fin, "%s %s", s + 1, t + 1);
    int64 Start_Time_Without_Read = clock();
    n = strlen(s + 1), m = strlen(t + 1);
    std::memset(dp, 0x3f, sizeof dp);
    std::memset(min, 0x3f, sizeof min);
    dp[0][0] = 0;
    for (int32 i = 1; i <= n; ++i) {
      for (int32 j = 2; j <= m; ++j) min[j] = min[j] + b;
      for (int32 j = 0; j <= m; ++j) {
        if (s[i] == t[j] && j > 0) dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]);
        dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + b);
        if (j > 0) dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + c);
        if (s[i - 1] == t[j] && j > 1)
          min[j] = std::min(min[j], dp[i - 2][j - 2]);
        if (i > 1 && j > 1 && s[i] == t[j - 1])
          dp[i][j] = std::min(dp[i][j], min[j] + d);
      }
      for (int32 j = 1; j <= m; ++j)
        dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + a);
    }
    fprintf(fout, "%d\n", dp[n][m]);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1309::main(), 0; }
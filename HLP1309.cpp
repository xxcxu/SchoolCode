#include <bits/stdc++.h>
namespace FileHeader {
  using int16 = int16_t;
  using int32 = int32_t;
  using int64 = int64_t;
  using uint32 = uint32_t;
  using uint64 = uint64_t;
  #define int32 int64
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
  int32 dp[N][N], nxt[2][N][26];
  char s[N], t[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    a = read(), b = read(), c = read(), d = read();
    fscanf(fin, "%s %s", s + 1, t + 1);
    int64 Start_Time_Without_Read = clock();
    n = strlen(s + 1), m = strlen(t + 1);
    for (int32 i = 0; i < 26; ++i) {
      nxt[0][n + 1][i] = n + 1;
      nxt[1][m + 1][i] = m + 1;
    }
    for (int32 i = n; i >= 1; --i) {
      for (int32 j = 0; j < 26; ++j) nxt[0][i][j] = nxt[0][i + 1][j];
      nxt[0][i][s[i] - 'a'] = i;
    }
    for (int32 i = m; i >= 1; --i) {
      for (int32 j = 0; j < 26; ++j) nxt[1][i][j] = nxt[1][i + 1][j];
      nxt[1][i][t[i] - 'a'] = i;
    }
    std::memset(dp, 0x3f, sizeof dp);  
    dp[0][0] = 0;
    auto cmin = [&](auto &x, auto y)->void { return x = (x < y ? x : y), void(); };
    s[n + 1] = 1, s[n + 2] = 4, t[m + 1] = 5, t[m + 2] = 9;
    for (int32 i = 0; i <= n; ++i) {
      for (int32 j = 0; j <= m; ++j) {
        if (s[i + 1] == t[j + 1]) cmin(dp[i + 1][j + 1], dp[i][j]);
        else cmin(dp[i + 1][j + 1], dp[i][j] + c);
        cmin(dp[i][j + 1], dp[i][j] + a);
        cmin(dp[i + 1][j], dp[i][j] + b);
        if (i > n - 2 || j > n - 2) continue;
        int32 t1 = nxt[0][i + 2][t[j + 1] - 'a'];
        int32 t2 = nxt[1][j + 2][s[i + 1] - 'a'];
        if (t1 > n || t2 > m) continue;
        cmin(dp[t1][t2], dp[i][j] + d + (t1 - i - 2) * b + (t2 - j - 2) * a);
      }
    }
    fprintf(fout, "%lld\n", dp[n][m]);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1309::main(), 0; }
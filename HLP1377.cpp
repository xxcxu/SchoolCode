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
namespace Solution_Of_HLP1377 {
  bool _1;
#pragma endregion
  static const i32 N = 1000005, M = (1 << 10);
  i32 n, m;
  std::vector<i32> p[N];
  char s1[N], s2[N];
  i32 need[N];
  bool dp[15][M];
  std::vector<i32> vec;
  bool _2;
  void _choose(i32 pos, char *s) {
    vec.clear();
    for (i32 i = 0; i < m; ++i) s[i] = '0';
    for (i32 q : p[pos]) s[m - q] = '1';
    i32 ppos = 0, qpos = 0;
    std::reverse(all(p[3 - pos]));
    for (i32 q : p[3 - pos]) if (s[m - q] == '1') { ppos = q; break; }
    for (i32 q : p[3 - pos])
      if (q >= ppos) {
        if (s[m - q] == '1') {
          while (s[m - q] == '1') ++q;
          vec.eb(q);
          qpos = q;
        }
        s[m - q] = '1';
        vec.eb(q);
      } else break;
    for (auto q : vec) if (q < qpos) s[m - q] = '0';
    std::reverse(all(p[3 - pos]));
    return void();
  }
  bool _compare(char *s, char *t) {
    for (i32 i = 0; i < m; ++i) {
      if (s[i] > t[i]) return false;
      if (s[i] < t[i]) return true;
    }
    return true;
  }
  void _print(i32 S) {
    for (i32 i = m - 1; i >= 0; --i)
      fprintf(fout, "%d", (S >> i & 1));
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) {
      i32 k = read();
      for (i32 j = 1; j <= k; ++j) p[i].eb(read());
    }
    i64 Start_Time_Without_Read = clock();
    if (n == 2) {
      _choose(1, s1);
      _choose(2, s2);
      if (_compare(s1, s2)) {
        fputs(s1, fout);
        fputs("\n", fout);
      } else {
        fputs(s2, fout);
        fputs("\n", fout);
      }
    } else {
      for (i32 i = 1; i <= n; ++i)
        for (i32 j : p[i]) need[i] |= (1 << (j - 1));
      for (i32 S = 0; S < (1 << 10); ++S)
        dp[0][S] = true;
      i32 lst = 0;
      for (i32 i = 1; i <= n; ++i) {
        if (!need[i]) continue;
        for (i32 T = 0; T < (1 << 10); ++T)
          if (dp[lst][T])
            for (i32 S = T; S < (1 << 10); ++S) {
              if ((S & T) != T) continue;
              if ((S ^ T) >= need[i])
                dp[i][S] = true;
            }
        lst = i;  
      }
      for (i32 S = 0; S < (1 << 10); ++S)
        if (dp[lst][S]) {
          _print(S);
          fputs("\n", fout);
          break;
        }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1377::main(), 0; }
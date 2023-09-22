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
namespace Solution_Of_HLP1308 {
  bool _1;
  static const int32 N = 10000005;
  int32 n, m;
  int32 a[N], b[N], c[N], min, minimin;
  uint32 x[N * 2], A, B, C;
  std::deque<std::array<int32, 3>> q;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    x[0] = read(), x[1] = read(), A = read(), B = read(), C = read();
    int64 Start_Time_Without_Read = clock();
    for (int32 i = 2; i <= 2 * m; ++i) x[i] = A * x[i - 2] + B * x[i - 1] + C;
    for (int32 i = 1; i <= m; ++i) a[i] = (x[i * 2 - 1] / 4) % n, b[i] = x[i * 2] / 4;
    for (int32 i = 0; i < n; ++i) c[i] = INT_MAX;
    uint32 power = 1, ans = 0;
    int32 min = INT_MAX, pos = -1;
    for (int32 i = 1; i <= m; ++i) {
      power *= 10099;
      c[a[i]] = b[i];
      if (pos != -1) {
        if (pos == a[i]) {
          if (b[i] > min) {
            min = b[i], pos = a[i];
            for (int32 j = 0; j < n; ++j)
              if (pos == -1 || c[j] < min) min = c[j], pos = j;
          } else {
            min = b[i];
          }
        } else {
          if (b[i] < min) min = b[i], pos = a[i];
        }
      } else {
        min = b[i];
        pos = a[i];
      }
      ans += 1u * min * power;
    }
    fprintf(fout, "%u\n", ans);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1308::main(), 0; }
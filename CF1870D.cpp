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
namespace Solution_Of_CF1970D {
  bool _1;
  static const int32 N = 200005;
  static const int32 inf32 = 0x3f3f3f3f;
  int32 n, k;
  int32 c[N], d[N];
  int32 suf[N];
  bool _2;
  void solve() {
    n = read();
    for (int32 i = 1; i <= n; ++i) c[i] = read();
    k = read();
    suf[n] = n;
    for (int32 i = n - 1; i >= 1; --i) suf[i] = (c[i] < c[suf[i + 1]]) ? i : suf[i + 1];
    int32 lst = 0, del = 0, lstans = inf32, now = k;
    for (int32 i = 1; i <= n; ++i) d[i] = 0;
    while (true) {
      int32 p = suf[lst + 1];
      if ((c[p] - del) > now || lst == n) break;
      int32 t = now / (c[p] - del);
      t = std::min(t, lstans);
      d[p] += t;
      now -= t * (c[p] - del);
      del = c[p];
      lst = p;
      lstans = t;
    }
    for (int32 i = n - 1; i >= 1; --i) d[i] = std::max(d[i], d[i + 1]);
    for (int32 i = 1; i <= n; ++i) fprintf(fout, "%d ", d[i]);
    fputs("\n", fout);
    return void();
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
signed main() { return Solution_Of_CF1970D::main(), 0; }
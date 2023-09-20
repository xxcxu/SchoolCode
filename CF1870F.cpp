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
  template<typename T>
  void read(T &t) {
    int32 f = t = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    t = f ? -t : t;
    return void();
  }
  template<typename T, typename ...Args>
  void read(T &x, Args &...args) { read(x); read(args...); }
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
namespace Solution_Of_CF1870F {
  bool _1;
  int64 n, k;
  bool _2;
  int64 up(int64 l, int64 r) {
    int64 ret = 0;
    while (l) {
      ret += r - l + 1;
      l /= k, r /= k;
    }
    return ret;
  }
  int64 down(int64 l, int64 r) {
    int64 ret = 0;
    while (l <= n / k) {
      l = l * k;
      r = (r <= n / k) ? (r * k) : (n + 1);
      ret += r - l;
    }
    return ret;
  }
  int64 check(int64 l, int64 mid) { return up(l, mid) + down(l, mid); }
  int64 binary_search(int64 l, int64 r, int32 duce) {
    int64 L = l;
    int64 ans = l - 1;
    while (l <= r) {
      int64 mid((l + r) >> 1);
      if (check(L, mid) <= mid - duce) l = mid + 1, ans = mid;
      else r = mid - 1;
    }
    return ans;
  }
  void solve() {
    read(n, k);
    int64 ans = 0;
    for (int64 l = 1, r; l <= n; l = r + 1) {
      r = (l <= n / k) ? (l * k - 1) : (n);
      ans += binary_search(l, r, 0) - binary_search(l, r, 1);
    }
    return fprintf(fout, "%lld\n", ans), void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    int32 t; read(t);
    int64 Start_Time_Without_Read = clock();
    while (t--) solve();
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1870F::main(), 0; }
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
namespace Solution_Of_CF1870C {
  bool _1;
  static const int32 N = 100005;
  int32 n, k;
  int32 a[N], pre[N], nxt[N], st[N][32];
  bool _2;
  void init(int32 *a, int32 n) {
    try {
      for (int32 i = 1; i <= n; ++i) st[i][0] = a[i];
      for (int32 j = 1; j <= 25; ++j)
        for (int32 i = 1; i + (1 << j) - 1 <= n; ++i)
          st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      throw 0;
    }
    catch (int number) { fprintf(ferr, "Return with Code %d\n", number); }
    catch (std::exception &e) { std::cerr << e.what() << std::endl; }
    return void();
  }
  int32 query(int32 l, int32 r) {
    int32 k = std::log2(r - l + 1);
    return std::max(st[l][k], st[r - (1 << k) + 1][k]);
  }
  void solve() {
    n = read(), k = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    init(a, n);
    std::memset(nxt, 0, sizeof nxt);
    std::memset(pre, 0x3f, sizeof pre);
    for (int32 i = 1; i <= n; ++i) {
      int32 l, r, ans;
      l = 1, r = n, ans = 0;
      while (l <= r) {
        int32 mid((l + r) >> 1);
        if (query(mid, n) >= a[i]) l = mid + 1, ans = mid;
        else r = mid - 1;
      }
      nxt[a[i]] = std::max(ans, nxt[a[i]]);
      l = 1, r = n, ans = 0;
      while (l <= r) {
        int32 mid((l + r) >> 1);
        if (query(1, mid) >= a[i]) r = mid - 1, ans = mid;
        else l = mid + 1;
      }
      pre[a[i]] = std::min(ans, pre[a[i]]);
    }
    for (int32 i = 1; i <= k; ++i) {
      if (!nxt[i]) fprintf(fout, "%d ", 0);
      else fprintf(fout, "%d ", (nxt[i] - pre[i] + 1) * 2);
    }
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
signed main() { return Solution_Of_CF1870C::main(), 0; }
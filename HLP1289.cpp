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
namespace Solution_Of_HLP1289 {
  static const int32 N = 100005;
  bool _1;
  int32 n, ans;
  int32 a[N], l[26][N], r[26][N], L[N], R[N], pre[N];
  struct st_table {
    int32 f[N][26], g[N][26];
    void init(int32 n, int32 *a, int32 *b) {
      for (int32 i = 1; i <= n; ++i)
        f[i][0] = a[i], g[i][0] = b[i];
      for (int32 j = 1; j <= 25; ++j)
        for (int32 i = 1; i + (1 << j) - 1 <= n; ++i) {
          f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
          g[i][j] = std::max(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
        }
      return void();
    }
    int32 query1(int32 l, int32 r) {
      int32 k = std::log2(r - l + 1);
      return std::min(f[l][k], f[r - (1 << k) + 1][k]);
    }
    int32 query2(int32 l, int32 r) {
      int32 k = std::log2(r - l + 1);
      return std::max(g[l][k], g[r - (1 << k) + 1][k]);
    }
  } s;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    auto st = clock();
    int32 ans = 0;
    for (int32 i = 1; i <= n; ++i) L[i] = R[i] = i;
    for (int32 i = 1; i <= n; ++i) l[0][i] = std::max(i - a[i], 1);
    for (int32 i = 1; i <= n; ++i) r[0][i] = std::min(i + a[i], n);
    for (int32 j = 1; j <= 25; ++j) {
      s.init(n, l[j - 1], r[j - 1]);
      for (int32 i = 1; i <= n; ++i)
        l[j][i] = s.query1(l[j - 1][i], r[j - 1][i]),
        r[j][i] = s.query2(l[j - 1][i], r[j - 1][i]);
    }
    // for (int32 j = 0; j <= 2; ++j) {
    //   fprintf(ferr, "Step: %d\n", 1 << j);
    //   for (int32 i = 1; i <= n; ++i) fprintf(ferr, "[%d %d] ", l[j][i], r[j][i]);
    //   fputs("\n", ferr);
    // }
    pre[0] = n + 1;
    for (int32 j = 25; j >= 0; --j) {
      s.init(n, l[j], r[j]);
      bool flag = false;
      for (int32 i = 1; i <= n; ++i) {
        int32 ql = s.query1(L[i], R[i]);
        int32 qr = s.query2(L[i], R[i]);
        pre[i] = std::min(pre[i - 1], qr);
        if (pre[ql - 1] < i) flag = true;
        if (flag) break;
      }
      if (flag) {
        ans += 1 << j;
        for (int32 i = 1; i <= n; ++i) {
          int32 ql = L[i], qr = R[i];
          L[i] = s.query1(ql, qr);
          R[i] = s.query2(ql, qr);
        }
      }
    }
    fprintf(fout, "%i\n", ans + 1);
    auto ed = clock();
    fprintf(ferr, "This code run in %ld ms\n", (ed - st));
    return void();
  }
}
signed main() { return Solution_Of_HLP1289::main(), 0; }
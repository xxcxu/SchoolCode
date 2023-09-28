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
namespace Solution_Of_CF612E {
  bool _1;
  static const int32 N = 1000005;
  int32 n, cir_cnt, a[N], ans[N];
  bool vis[N];
  std::vector<int32> siz[N], cir[N];
  bool _2;
  void odd(int32 x) {
    int32 n = cir[x].size();
    for (int32 i = 0, j = n / 2 + 1; j < n; ++i, ++j) {
      ans[cir[x][i]] = cir[x][j];
      ans[cir[x][j]] = cir[x][i + 1];
    }
    ans[cir[x][n / 2]] = cir[x][0];
    return void();
  }
  void even(int32 x, int32 y) {
    int32 n = cir[x].size();
    for (int32 i = 0; i < n; ++i) {
      ans[cir[x][i]] = cir[y][i];
      ans[cir[y][i]] = cir[x][(i + 1) % n];
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    int64 Start_Time_Without_Read = clock();
    for (int32 i = 1; i <= n; ++i) {
      if (vis[i]) continue;
      ++cir_cnt;
      int32 u = i;
      do { cir[cir_cnt].eb(u); vis[u] = true, u = a[u]; } while (u != i);
      siz[(int32)cir[cir_cnt].size()].eb(cir_cnt);
    }
    for (int32 i = 2; i <= n; i += 2) {
      if (siz[i].empty()) continue;
      if ((int32)siz[i].size() % 2 == 1) {
        fputs("-1\n", fout);
        return void();
      }
    }
    for (int32 i = 1; i <= n; i += 2)
      for (int32 c : siz[i]) odd(c);
    for (int32 i = 2; i <= n; i += 2) {
      int32 lst = 0;
      for (int32 c : siz[i]) {
        if (lst) even(c, lst), lst = 0;
        else lst = c;
      }
    }
    for (int32 i = 1; i <= n; ++i) fprintf(fout, "%d ", ans[i]);
    fputs("\n", fout);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF612E::main(), 0; }
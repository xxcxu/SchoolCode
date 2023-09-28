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
namespace Solution_Of_CF1879E {
  bool _1;
  static const int32 N = 105;
  int32 n;
  int32 p[N], d[N], c[N];
  std::vector<int32> e[N];
  bool _2;
  void dfs(int32 x) {
    d[x] = d[p[x]] + 1;
    for (int32 y : e[x]) dfs(y);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (int32 i = 2; i <= n; ++i) {
      p[i] = read();
      e[p[i]].eb(i);
    }
    int64 Start_Time_Without_Read = clock();
    dfs(1);
    if (*std::max_element(d + 1, d + n + 1) <= 2) {
      fprintf(fout, "%d\n", 1);
      fflush(fout);
      for (int32 i = 2; i <= n; ++i) fprintf(fout, "%d%c", 1, " \n"[i == n]), fflush(fout);
      while (true) {
        int32 op = read();
        if (op == -1) assert(0);
        if (op == 1) break;
        if (op != 0) assert(0);
        int32 cnt[2] = {0, 0};
        for (int32 i = 1; i <= 1; ++i) cnt[i] = read();
        fprintf(fout, "%d\n", 1);
        fflush(fout);
      }
    } else {
      bool flag = false;
      for (int32 i = 2; i <= n; ++i)
        if (e[i].size() == 1)
          flag = true;
      if (!flag) {
        fprintf(fout, "%d\n", 2);
        fflush(fout);
        c[1] = 1;
        for (int32 i = 2; i <= n; ++i) c[i] = 3 - c[p[i]];
        for (int32 i = 2; i <= n; ++i) fprintf(fout, "%d%c", c[i], " \n"[i == n]), fflush(fout);
        while (true) {
          int32 op = read();
          if (op == -1) assert(0);
          if (op == 1) break;
          if (op != 0) assert(0);
          int32 cnt[3] = {0, 0, 0};
          for (int32 i = 1; i <= 2; ++i) cnt[i] = read();
          fprintf(fout, "%d\n", (cnt[1] == 1) ? 1 : 2);
          fflush(fout);
        }
      } else {
        bool flag2 = true;
        for (int32 i = 2; i <= n; ++i)
          if (e[p[i]].size() >= 1 && e[i].size() == 1 && e[e[i][0]].size() == 1)
            flag2 = false;
        int32 k;
rebuild:
        for (int32 i = 2; i <= n; ++i) {
          if (!flag2) c[i] = d[i] % 3 + 1;
          else {
            if ((e[p[i]].size() >= 1 && e[i].size() == 1) || (e[p[i]].size() == 1)) {
              if (e[p[i]].size() >= 1 && e[i].size() == 1) c[i] = 1;
              else c[i] = 2;
            }
          }
        }
        if (flag2) {
          c[1] = 1;
          for (int32 i = 2; i <= n; ++i) {
            if (c[i]) {
              int32 x = i;
              while (p[x] != 1) {
                if (c[p[x]] && c[p[x]] != 3 - c[x]) { flag2 = false; goto rebuild; }
                c[p[x]] = 3 - c[x];
                x = p[x];
              }
            }
          }
          for (int32 i = 2; i <= n; ++i) {
            if (!c[i]) c[i] = 3 - c[p[i]];
          }
          fprintf(fout, "%d\n", k = 2);
          fflush(fout);
          for (int32 i = 2; i <= n; ++i) fprintf(fout, "%d%c", c[i], " \n"[i == n]), fflush(fout);
          while (true) {
            int32 op = read();
            if (op == -1) assert(0);
            if (op == 1) break;
            if (op != 0) assert(0);
            int32 cnt[3] = {0, 0, 0};
            for (int32 i = 1; i <= k; ++i) cnt[i] = read();
            int32 to = -1;
            if (cnt[1] == 1 && cnt[2] == 1) to = 1;
            else if (cnt[1] == 1) to = 1;
            else if (cnt[2] == 1) to = 2;
            assert(to != -1);
            fprintf(fout, "%d\n", to);
            fflush(fout);
          }
        } else {
          fprintf(fout, "%d\n", k = 3);
          fflush(fout);
          for (int32 i = 2; i <= n; ++i) fprintf(fout, "%d%c", c[i], " \n"[i == n]), fflush(fout);
          while (true) {
            int32 op = read();
            if (op == -1) assert(0);
            if (op == 1) break;
            if (op != 0) assert(0);
            int32 cnt[4] = {0, 0, 0, 0};
            for (int32 i = 1; i <= k; ++i) cnt[i] = read();
            int32 to = -1;
            if (cnt[1] == 0 && cnt[2] >= 1 && cnt[3] >= 1) to = 2;
            else if (cnt[2] == 0 && cnt[1] >= 1 && cnt[3] >= 1) to = 3;
            else if (cnt[3] == 0 && cnt[1] >= 1 && cnt[2] >= 1) to = 1;
            else if (cnt[1] == 1) to = 1;
            else if (cnt[2] == 1) to = 2;
            else if (cnt[3] == 1) to = 3;
            assert(to != -1);
            fprintf(fout, "%d\n", to);
            fflush(fout);
          }
        }
      }
    }
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1879E::main(), 0; }
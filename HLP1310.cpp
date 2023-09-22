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
namespace Solution_Of_HLP1310 {
  bool _1;
  static const int32 N = 1005, M = 2 * N;
  static const int32 dx[] = {-1, -1, -2, -2, 1, 1, 2, 2};
  static const int32 dy[] = {2, -2, 1, -1, 2, -2, 1, -1};
  int32 n, m;
  std::map<int32, std::map<int32, int32>> step;
  int32 calc(int32 x) {
    if (x % 4 == 0) return x / 2;
    else return (x + 2) / 2;
  }
  void solve() {
    n = read(), m = read();
    if (n == m) {
      if (n == 0) fprintf(fout, "%d\n", 0);
      else if (n == 1) fprintf(fout, "%d\n", 2);
      else if (n == 2) fprintf(fout, "%d\n", 4);
      else if (n == 3) fprintf(fout, "%d\n", 2);
      else fprintf(fout, "%d\n", ((n - 4) / 3) * 2 + 4);
      return void();
    }
    if (n == 0) std::swap(n, m);
    if (m == 0) {
      if (n & 1) {
        if (n == 1) fprintf(fout, "%d\n", 3);
        else if (n == 3) fprintf(fout, "%d\n", 3);
        else if (n == 5) fprintf(fout, "%d\n", 3);
        else fprintf(fout, "%d\n", std::min({calc(n - 1), calc(n - 3), calc(n - 5)}) + 3);
      } else {
        if (n % 4 == 0) {
          fprintf(fout, "%d\n", n / 2);
        } else {
          fprintf(fout, "%d\n", (n + 2) / 2);
        }
      }
      return void();
    }
    std::queue<std::array<int32, 2>> q;
    step.clear();
    q.push({N, N});
    step[N][N] = 0;
    while (q.size()) {
      auto &[x, y] = q.front(); q.pop();
      if (x == n + N && y == m + N) break;
      for (int32 i = 0; i < 8; ++i) {
        int32 nx = x + dx[i], ny = y + dy[i];
        if (!step[nx].count(ny) && nx > 0 && nx < M && ny > 0 && ny < M) {
          step[nx][ny] = step[x][y] + 1;
          q.push({nx, ny});
        }
      }
    }
    fprintf(fout, "%d\n", step[n + N][m + N]);
    return void();
  }
  bool _2;
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
signed main() { return Solution_Of_HLP1310::main(), 0; }
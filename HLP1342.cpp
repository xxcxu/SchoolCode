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
namespace Solution_Of_device {
  bool _1;
#pragma endregion
  static const i32 N = 1005;
  i32 n, k;
  i32 p[N], sum[N][N];
  i32 step[N][N];
  std::vector<i32> vec[N];
  bool _2;
  bool check(i32 x) {
    if (x % 10 == 0) return false;
    if (x / 10 % 10 == 0) return false;
    if (x / 100 == 0) return false;
    return true;
  }
  i32 get(i32 x, i32 d) {
    for (i32 i = 1; i < d; ++i) x /= 10;
    return x % 10;
  }
  void dfs(i32 x, i32 now, i32 d) {
    if (now == 7) {
      if (d != 4) return void();
      vec[x / 1001].eb(p[0] * 100 + p[1] * 10 + p[2]);
      vec[x / 1001].eb(p[0] * 100 + p[2] * 10 + p[1]);
      vec[x / 1001].eb(p[1] * 100 + p[0] * 10 + p[2]);
      vec[x / 1001].eb(p[1] * 100 + p[2] * 10 + p[0]);
      vec[x / 1001].eb(p[2] * 100 + p[0] * 10 + p[1]);
      vec[x / 1001].eb(p[2] * 100 + p[1] * 10 + p[0]);
      return void();
    }
    if (d <= 4) {
      dfs(x, now + 1, d);
      if (d <= 3 && get(x, now) != 0) {
        p[d - 1] = get(x, now);
        dfs(x, now + 1, d + 1);
      }
    }
    return void();
  }
  void init() {
    for (i32 i = 111; i <= 999; ++i)
      if (check(i)) {
        dfs(i * 1001, 1, 1);
        std::sort(all(vec[i]));
        vec[i].erase(std::unique(all(vec[i])), vec[i].end());
      }
    std::memset(step, -1, sizeof step);
    for (i32 i = 111; i <= 999; ++i)
      if (check(i)) {
        std::queue<i32> q;
        q.ep(i);
        step[i][i] = 0;
        while (q.size()) {
          i32 u = q.front(); q.pop();
          for (i32 v : vec[u]) {
            if (step[i][v] == -1) {
              step[i][v] = step[i][u] + 1;
              q.ep(v);
            }
          }
        }
        for (i32 j = 111; j <= 999; ++j)
          if (check(j) && step[i][j] != -1) ++sum[i][step[i][j]];
        for (i32 j = 1; j <= 999; ++j) sum[i][j] += sum[i][j - 1];
      }
    return void();
  }
  void solve() {
    n = read(), k = read();
    k = std::min(k, 999);
    fprintf(fout, "%d\n", sum[n][k]); 
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("device.in", "r");
    // fout = fopen("device.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    init();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_device::main(), 0; }
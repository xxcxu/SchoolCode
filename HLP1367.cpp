#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using ui32 = uint32_t;
  using ui64 = uint64_t;
  #define i32 i64
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  i64 read() {
    i64 t = 0, f = 0;
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
namespace Solution_Of_HLP1367 {
  bool _1;
#pragma endregion
  static const i32 N = 300005;
  i32 n; i64 L, R;
  i32 l[N], p[N];
  i64 sum_m[N], sum_l[N];
  double ans;
  bool _2;
  double calc(i32 l, i32 r, i64 M) {
    if (r > n) return 0.0;
    i64 sm = sum_m[r - 1] - sum_m[l - 1];
    i64 sl = sum_l[r - 1] - sum_l[l - 1];
    double rl = 1.0 * (M - sm) / p[r];
    return 1.0 * M / (sl + rl);
  }
  void solve() {
    for (i32 i = 1; i <= n; ++i) sum_l[i] = sum_l[i - 1] + l[i];
    for (i32 i = 1; i <= n; ++i) sum_m[i] = sum_m[i - 1] + 1ll * l[i] * p[i];
    for (i32 i = 1, j = 0; i <= n; ++i) {
      while (j <= n && sum_m[j] - sum_m[i - 1] < L) ++j;
      ans = std::max(ans, calc(i, j, L));
    }
    for (i32 i = 1, j = 1; i <= n; ++i) {
      while (j <= n && sum_m[j] - sum_m[i - 1] < R) ++j;
      ans = std::max(ans, calc(i, j, R));
    }
    return void();
  }
  std::deque<std::pair<i32, double>> q;
  void add(i32 x, double mid) {
    while (q.size() && q.back().second <= sum_m[x] - 1.0 * sum_l[x] * mid) q.pop_back();
    q.push_back(std::make_pair(x, sum_m[x] - 1.0 * sum_l[x] * mid));
    return void();
  }
  void del(i32 x) {
    while (q.size() && q.front().first <= x) q.pop_front();
    return void();
  }
  bool check(double mid) {
    q.clear();
    for (i32 i = 1, j = 1, k = 1; i <= n; ++i) {
      while (k <= n && sum_m[k] - sum_m[i - 1] < R) add(k++, mid);
      while (j <= n && sum_m[j] - sum_m[i - 1] < L) del(j++);
      del(j);
      if (q.size() && q.front().second >= sum_m[i - 1] - 1.0 * sum_l[i - 1] * mid) return true;
    }
    return false;
  }
  void B1narySearch() {
    static constexpr double eps = 1e-9;
    double l = 0, r = 1e6;
    while (r - l > eps) {
      double mid((l + r) / 2);
      if (check(mid)) l = mid;
      else r = mid;
    }
    ans = std::max(ans, l);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), L = read(), R = read();
    for (i32 i = 1; i <= n; ++i) l[i] = read();
    for (i32 i = 1; i <= n; ++i) p[i] = read();
    i64 Start_Time_Without_Read = clock();
    solve();
    std::reverse(l + 1, l + n + 1);
    std::reverse(p + 1, p + n + 1);
    solve();
    B1narySearch();
    fprintf(fout, "%.10lf\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1367::main(), 0; }
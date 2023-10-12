#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using u32 = uint32_t;
  using u64 = uint64_t;
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
namespace Solution_Of_HLP1376 {
  bool _1;
#pragma endregion
  static const i32 N = 100005;
  static const u64 P = 233;
  i32 n;
  i32 id[N], ans[N];
  u64 power[N], hash[N];
  std::vector<std::pair<i32, i32>> vec[N];
  char s[N];
  struct TreeArray {
    i32 s[N];
    void add(i32 x, i32 v) {
      for (; x < N; x += x & -x)
        s[x] += v;
      return void();
    }
    i32 ask(i32 x) {
      i32 ans = 0;
      for (; x >= 1; x -= x & -x)
        ans += s[x];
      return ans;
    }
  } tr;
  bool _2;
  u64 _get(i32 l, i32 r) { return hash[r] - hash[l - 1] * power[r - l + 1]; }
  bool _equal(i32 l, i32 r, i32 L, i32 R) { return _get(l, r) == _get(L, R); }
  i32 _lcp(i32 l1, i32 r1, i32 l2, i32 r2) {
    i32 n1 = r1 - l1 + 1;
    i32 n2 = r2 - l2 + 1;
    i32 l = 0, r = std::min(n1, n2), ans = 0;
    auto _check = [&](i32 L)->bool { return _equal(l1, l1 + L - 1, l2, l2 + L - 1); };
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (_check(mid)) l = mid + 1, ans = mid;
      else r = mid - 1;
    }
    return ans;
  }
  bool cmp1(i32 l1, i32 r1, i32 l2, i32 r2) { // <=
    // s[l1 ... r1] <= s[l2 ... r2]
    i32 lcp = _lcp(l1, r1, l2, r2);
    i32 n1 = r1 - l1 + 1;
    i32 n2 = r2 - l2 + 1;
    if (lcp == std::min(n1, n2)) return n1 <= n2;
    return s[l1 + lcp] <= s[l2 + lcp];
  }
  bool cmp2(i32 l1, i32 r1, i32 l2, i32 r2) { // <
    // s[l1 ... r1] < s[l2 ... r2]
    i32 lcp = _lcp(l1, r1, l2, r2);
    i32 n1 = r1 - l1 + 1;
    i32 n2 = r2 - l2 + 1;
    if (lcp == std::min(n1, n2)) return n1 < n2;
    return s[l1 + lcp] < s[l2 + lcp];
  }
  bool check(i32 p, i32 op, i32 mid) {
    i32 len = n - id[p] + 1;
    auto foo = op ? cmp2 : cmp1;
    if (_equal(id[p], id[p] + len - 1, id[mid], id[mid] + len - 1))
      return foo(id[p], id[p] + len - 1, id[mid] + len, std::min(id[mid] + 2 * len - 1, n));
    return foo(id[p], id[p] + len - 1, id[mid], id[mid] + len - 1);
  }
  i32 binary_search(i32 p, i32 op) {
    i32 l = p, r = n + 1, ans = 0;
    while (l <= r) {
      i32 mid((l + r) >> 1);
      if (check(p, op, mid)) r = mid - 1, ans = mid;
      else l = mid + 1;
    }
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    i64 Start_Time_Without_Read = clock();
    power[0] = 1;
    for (i32 i = 1; i <= n; ++i) power[i] = power[i - 1] * P;
    for (i32 i = 1; i <= n; ++i) hash[i] = hash[i - 1] * P + (s[i] - 'a');
    for (i32 i = 1; i <= n; ++i) id[i] = i;
    std::sort(id + 1, id + n + 1, [&](const i32& x, const i32& y) { return cmp2(x, n, y, n); });
    for (i32 i = 1; i <= n; ++i) {
      i32 len = n - id[i] + 1;
      if (3 * len < n) {
        i32 l = binary_search(i, 0);
        i32 r = binary_search(i, 1);
        vec[l].eb(3 * len, 1);
        vec[r].eb(3 * len, -1);
      }
    }
    for (i32 i = 1; i <= n; ++i) {
      for (auto [j, k] : vec[i]) tr.add(j, k);
      ans[id[i]] += tr.ask(n - id[i]);
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d%c", ans[i], " \n"[i == n]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1376::main(), 0; }
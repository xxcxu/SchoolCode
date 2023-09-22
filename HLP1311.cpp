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
namespace Solution_Of_HLP1311 {
  bool _1;
  static const int32 N = 100005;
  int32 n, m, k, now;
  int32 a[N], b[N], ans[N], cnt[N];
  std::unordered_set<int32> s;
  struct qnode {
    int32 l, r, id;
    qnode() = default;
    qnode(int32 l, int32 r, int32 id):
      l(l), r(r), id(id) {}
  } q[N];
  bool _2;
  void discrete() {
    std::memcpy(b + 1, a + 1, n * sizeof(int32));
    std::sort(b + 1, b + n + 1);
    k = std::unique(b + 1, b + n + 1) - b - 1;
    for (int32 i = 1; i <= n; ++i)
      a[i] = std::lower_bound(b + 1, b + k + 1, a[i]) - b;
    return void();
  }
  void add(int32 x) {
    ++cnt[a[x]];
    if (cnt[a[x]] == 1) ++now;
    return void();
  }
  void del(int32 x) {
    --cnt[a[x]];
    if (cnt[a[x]] == 0) --now;
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (int32 i = 1; i <= n; ++i) a[i] = read();
    int64 Start_Time_Without_Read = clock();
    if (n <= 1000 && m <= 1000) {
      for (int32 t = 1; t <= m; ++t) {
        static int32 op, l, r, x;
        op = read(), l = read(), r = read();
        if (op == 1) {
          x = read();
          for (int32 i = l; i <= r; ++i) a[i] = x;
        } else {
          s.clear();
          for (int32 i = l; i <= r; ++i) s.ep(a[i]);
          fprintf(fout, "%lld\n", s.size());
        }
      }
    } else {
      discrete();
      for (int32 i = 1; i <= m; ++i) {
        static int32 ignore = 0;
        ignore = read();
        q[i].l = read(), q[i].r = read(), q[i].id = i;
      }
      int32 B = std::sqrt(n);
      std::sort(q + 1, q + m + 1, [&](const qnode &a, const qnode &b)
        {
          if ((a.l - 1) / B != (b.l - 1) / B) return a.l < b.l;
          else return (((a.l - 1) / B) & 1) ? a.r > b.r : a.r < b.r;
        });
      int32 L = 1, R = 0;
      now = 0;
      for (int32 i = 1; i <= m; ++i) {
        auto [l, r, id] = q[i];
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) del(L++);
        while (R > r) del(R--);
        ans[id] = now;
      }
      for (int32 i = 1; i <= m; ++i)
        fprintf(fout, "%d\n", ans[i]);
    }
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1311::main(), 0; }
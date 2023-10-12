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
namespace Solution_Of_HLP1379 {
  bool _1;
#pragma endregion
  static const i32 N = 500005;
  i32 n, m;
  i32 a[N], lst[N], pre[N];
  bool _2;
  struct SegmentTree {
    i32 tr[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        tr[x] += v;
        return void();
      }
      i32 mid((l + r) >> 1);
      if (ql <= mid) modify(ls, l, mid, ql, qr, v);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
      return void();
    }
    i32 query(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) return tr[x];
      i32 mid((l + r) >> 1);
      if (p <= mid) return query(ls, l, mid, p) + tr[x];
      else return query(rs, mid + 1, r, p) + tr[x];
    }
  } seg;
  struct TreeArray {
    i32 s[N];
    void add(i32 x, i32 v) {
      for (x = x + 1; x <= m + 1; x += x & -x)
        s[x] += v;
      return void();
    }
    i32 ask(i32 x) {
      i32 ans = 0;
      for (x = x + 1; x >= 1; x -= x & -x)
        ans += s[x];
      return ans;
    }
  } tr;
  struct qNode {
    i32 p, q, v, id;
    qNode() = default;
    qNode(i32 _p, i32 _q, i32 _v, i32 _id):
      p(_p), q(_q), v(_v), id(_id) {}
  };
  std::vector<qNode> querys;
  i32 ans[N], cnt[N];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= m; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= m; ++i) {
      pre[i] = lst[a[i]];
      lst[a[i]] = i;
    }
    for (i32 i = 1; i <= m; ++i) {
      if (!pre[i]) seg.modify(1, 1, n, 1, n, 1);
      else if (pre[i] + 1 <= i - 1) {
        querys.eb(pre[i], pre[i], -1, i);
        querys.eb(i - 1, pre[i], 1, i);
      }
    }
    std::sort(all(querys), [&](const qNode &a, const qNode &b) { return a.p < b.p; });
    i32 point = 0;
    for (auto [p, q, v, id] : querys) {
      while (point < p) tr.add(pre[++point], 1);
      ans[id] += tr.ask(q) * v;
    }
    for (i32 i = 1; i <= m; ++i)
      if (ans[i]) seg.modify(1, 1, n, 1, ans[i], 1);
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d ", seg.query(1, 1, n, i));
    fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1379::main(), 0; }
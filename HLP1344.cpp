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
namespace Solution_Of_badge {
  bool _1;
#pragma endregion 
  static const i32 N = 500005;
  static const i32 B = 550;
  i32 n, q;
  i32 p[N], ans[N], sum[N], lst[N], nxt[N], pre[N];
  std::vector<i32> vec[N];
  struct Vertex {
    i32 l, r;
    Vertex() = default;
    Vertex(i32 l, i32 r): l(l), r(r) {}
  } a[N];
  struct Node {
    i32 v, id;
    Node() = default;
    Node(i32 v, i32 id): v(v), id(id) {}
  };
  std::vector<Node> vx;
  struct TreeArray {
    i32 s[N];
    void add(i32 x, i32 v) {
      for (; x <= n; x += x & -x)
        s[x] += v;
      return void();
    }
    i32 ask(i32 x) {
      i32 ans = 0;
      for (; x; x -= x & -x)
        ans += s[x];
      return ans;
    }
  } t1;
  bool _2;
  bool inRange(i32 l, i32 x, i32 r) { return l <= x && x <= r; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("badge0.in", "r");
    // fout = fopen("badge0.out", "w");
    // fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), q = read();
    for (i32 i = 1; i <= n; ++i) a[i].l = read(), a[i].r = read();
    std::sort(a + 1, a + n + 1, [&](const Vertex &a, const Vertex &b) { return a.l != b.l ? a.l < b.l : a.r < b.r; });
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= q; ++i) {
      static i32 m;
      m = read();
      if (m >= B) {
        for (i32 j = 1; j <= m; ++j) p[i] = read();
        for (i32 j = 1; j <= m; ++j) ++sum[p[j]];
        for (i32 j = 1; j <= n; ++j) sum[j] += sum[j - 1];
        for (i32 j = 1; j <= n; ++j) if ((sum[a[j].r] - sum[a[j].l - 1]) & 1) ++ans[i];
        for (i32 j = 1; j <= n; ++j) sum[j] = 0;
      } else {
        for (i32 j = 1; j <= m; ++j) vx.eb(read(), i);
      }
    }
    vx.eb(0, 0), vx.eb(n + 1, 0);
    std::sort(all(vx), [&](const Node &x, const Node &y) { return x.v < y.v; });
    i32 m = vx.size();
    std::fill(lst + 1, lst + n + 1, m - 1);
    nxt[m - 1] = m;
    nxt[m] = m;
    std::fill(pre + 1, pre + m, 0);
    for (i32 i = m - 2; i > 0; --i) {
      nxt[i] = lst[vx[i].id];
      pre[nxt[i]] = i;
      lst[vx[i].id] = i;
    }
    /*
    x[l - 1] < a[i].l <= x[l]
    x[r] <= a[i].r < x[r + 1]
    */
    for (i32 i = 1, p = 1; i < m - 1; ++i) {
      while (p <= n && a[p].l <= vx[i].v) t1.add(a[p++].r, 1);
      for (i32 j = nxt[i], k = i; j < m; k = nxt[j], j = nxt[k]) {
        i32 res = 0;
        res += t1.ask(vx[j].v - 1); // a[i].l <= x[l] && a[i].r < x[r + 1]
        res -= t1.ask(vx[k].v - 1); // a[i].l <= x[l] && a[i].r < x[r]
        if (nxt[j] < m) {
          ans[vx[nxt[i]].id] -= t1.ask(vx[nxt[j]].v - 1);
          ans[vx[nxt[i]].id] += t1.ask(vx[j].v - 1);
        }
        ans[vx[i].id] += res;
      }
    }
    for (i32 i = 1; i <= q; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time_Without_Read = clock();
    // fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_badge::main(), 0; }
/*
复活赛4强对战表：
ul vs 安倍晋三
汉堡(野狐) vs 牢大
*/
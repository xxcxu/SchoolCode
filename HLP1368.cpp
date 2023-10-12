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
namespace Solution_Of_HLP1368 {
  bool _1;
#pragma endregion
  static const i32 N = 5005;
  static const i32 P = 998244353;
  i32 n, k, ans;
  i32 a[N];
  i32 ts;
  i32 redfn[N], dep[N], dfn[N], size[N], son[N], top[N], fa[N];
  std::vector<i32> e[N];
  bool _2;
  void dfs1(i32 x, i32 f) {
    fa[x] = f;
    dep[x] = dep[f] + 1;
    size[x] = 1;
    for (i32 y : e[x])
      if (y != f) {
        dfs1(y, x);
        size[x] += size[y];
        if (size[y] > size[son[x]]) son[x] = y;
      }
    return void();
  }
  void dfs2(i32 x, i32 tp) {
    top[x] = tp;
    dfn[x] = ++ts;
    redfn[ts] = x;
    if (son[x]) dfs2(son[x], tp);
    for (i32 y : e[x])
      if (y != fa[x] && y != son[x])
        dfs2(y, y);
    return void();
  }
  struct SegmentTree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    i32 tr[N << 2], ers[N << 2], tag[N << 2];
    void build(i32 x, i32 l, i32 r) {
      tr[x] = 0, ers[x] = 0;
      if (l == r)
        return tr[x] = size[redfn[l]], void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return void();
    }
    void modify1(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        tr[x] += v;
        return void();
      }
      i32 mid((l + r) >> 1);
      if (ql <= mid) modify1(ls, l, mid, ql, qr, v);
      if (qr > mid) modify1(rs, mid + 1, r, ql, qr, v);
      return void();
    }
    void modify2(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        ers[x] += v;
        return void();
      }
      i32 mid((l + r) >> 1);
      if (ql <= mid) modify2(ls, l, mid, ql, qr, v);
      if (qr > mid) modify2(rs, mid + 1, r, ql, qr, v);
      return void();
    }
    i32 query1(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x];
      i32 mid((l + r) >> 1);
      if (p <= mid) return query1(ls, l, mid, p) + tr[x];
      return query1(rs, mid + 1, r, p) + tr[x];
    } 
    i32 query2(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return ers[x];
      i32 mid((l + r) >> 1);
      if (p <= mid) return query2(ls, l, mid, p) + ers[x];
      return query2(rs, mid + 1, r, p) + ers[x];
    }
  } seg;
  void modify_chain(i32 x, i32 y, i32 v) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
      seg.modify1(1, 1, n, dfn[top[x]], dfn[x], v);
      x = fa[top[x]];
    }
    if (dfn[x] < dfn[y]) std::swap(x, y);
    seg.modify1(1, 1, n, dfn[y], dfn[x], v);
    return void();
  }
  void modify_subtree(i32 x, i32 v) {
    seg.modify2(1, 1, n, dfn[x], dfn[x] + size[x] - 1, v);
    return void();
  }
  void dfs3(i32 root, i32 x) {
    if (x == k + 1) {
      ++ans;
      return void();
    }
    for (i32 i = 1; i <= n; ++i) {
      if (dfn[root] < dfn[i] && dfn[i] < dfn[root] + size[root])
        if (seg.query2(1, 1, n, dfn[i]) == 0) {
          i32 all = seg.query1(1, 1, n, dfn[root]);
          i32 sub = seg.query1(1, 1, n, dfn[i]);
          if (all - sub == a[x]) {
            modify_chain(1, i, -sub);
            modify_subtree(i, 1);
            dfs3(root, x + 1);
            modify_chain(1, i, sub);
            modify_subtree(i, -1);
          }
          if (sub == a[x]) {
            dfs3(i, x + 1);
          }
        }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i < n; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
    }
    k = read();
    for (i32 i = 1; i <= k; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    dfs1(1, 0);
    dfs2(1, 1);
    seg.build(1, 1, n);
    dfs3(1, 1);
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1368::main(), 0; }
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
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
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
namespace Solution_Of_HLP124 {
  bool _1;
#pragma endregion
  static const i32 N = 200005;
  i32 n, k, ts, s[N], t[N];
  i32 son[N], dep[N], fa[N], size[N], dfn[N], top[N];
  std::vector<i32> e[N];
  struct SegmentTree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    i32 tr[N << 2], tag[N << 2];
    void pushup(i32 x) {
      tr[x] = tr[ls] + tr[rs];
      return void();
    }
    void pushdown(i32 x, i32 l, i32 r) {
      i32 mid((l + r) >> 1);
      i32 llen(mid - l + 1), rlen(r - mid);
      if (tag[x]) {
        tr[ls] += llen * tag[x]; tag[ls] += tag[x];
        tr[rs] += rlen * tag[x]; tag[rs] += tag[x];
        tag[x] = 0;
      }
      return void();
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        tr[x] += v * (r - l + 1);
        tag[x] += v;
        return void();
      }
      i32 mid((l + r) >> 1);
      pushdown(x, l, r);
      if (ql <= mid) modify(ls, l, mid, ql, qr, v);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    i32 query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return tr[x];
      i32 mid((l + r) >> 1), ans(0);
      pushdown(x, l, r);
      if (ql <= mid) ans += query(ls, l, mid, ql, qr);
      if (qr > mid) ans += query(rs, mid + 1, r, ql, qr);
      return ans;
    }
  } tr;
  bool _2;
  void dfs(i32 x) {
    dep[x] = dep[fa[x]] + 1;
    size[x] = 1;
    for (i32 y : e[x]) {
      dfs(y);
      size[x] += size[y];
      if (size[y] > size[son[x]]) son[x] = y;
    }
    return void();
  }
  void dfs(i32 x, i32 t) {
    dfn[x] = ++ts;
    top[x] = t;
    if (son[x]) dfs(son[x], t);
    for (i32 y : e[x]) if (y != son[x] && y != fa[x]) dfs(y, y);
    return void();
  }
  void modifyPath(i32 x, i32 y, i32 v) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
      tr.modify(1, 1, n, dfn[top[x]], dfn[x], v); 
      x = fa[top[x]];
    }
    if (dfn[x] < dfn[y]) std::swap(x, y);
    tr.modify(1, 1, n, dfn[y], dfn[x], v);
    return void();
  }
  i32 queryPath(i32 x, i32 y) {
    i32 ans = 0;
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
      ans += tr.query(1, 1, n, dfn[top[x]], dfn[x]);
      x = fa[top[x]];
    }
    if (dfn[x] < dfn[y]) std::swap(x, y);
    ans += tr.query(1, 1, n, dfn[y], dfn[x]);
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read(); 
    for (i32 i = 2; i <= n; ++i) {
      fa[i] = read();
      e[fa[i]].eb(i);
    }
    for (i32 i = 1; i <= k; ++i) s[i] = read(), t[i] = read();
    i64 Start_Time_Without_Read = clock();
    dfs(1), dfs(1, 1);
    i32 ans = 0, p1 = 0, p2 = 0;
    for (i32 i = 1; i <= k; ++i) {
      modifyPath(s[i], t[i], 1);
      for (i32 j = 1; j <= k; ++j)
        if (j != i)
          if (i32 ret; (ret = queryPath(s[j], t[j])) > ans)
            ans = ret, p1 = i, p2 = j;
      modifyPath(s[i], t[i], -1);
    }
    fprintf(fout, "%d\n%d %d\n", ans - 1, p1, p2);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP124::main(), 0; }
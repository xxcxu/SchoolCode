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
}
using namespace FileHeader;
namespace Solution_Of_P7983 {
  bool _1;
#pragma endregion
  static const i32 N = 505, B = 35, M = N / B + 5;
  i32 n, m, a[N], b[N];
  i32 bel[N], L[N], R[N];
  namespace blk1 {
    // O(sqrtn) modify sum_a
    // O(1) query sum_a
    i32 a[N], sum[N][B + 5], tag[M], pre[M];
    void init() {
      for (i32 i = 1; i <= n; ++i) {
        tag[i] = 0;
        blk1::a[i] = Solution_Of_P7983::a[i]; 
      }
      for (i32 i = 1; i <= bel[n]; ++i)
        for (i32 j = L[i]; j <= R[i]; ++j)
          sum[i][j - L[i] + 1] = sum[i][j - L[i]] + a[j];
      for (i32 i = 1; i <= bel[n]; ++i)
        pre[i] = pre[i - 1] + sum[i - 1][R[i - 1] - L[i - 1] + 1];
      return void();
    }
    void modify(i32 l, i32 r, i32 v) {
      i32 p = bel[l], q = bel[r];
      if (p == q) {
        if (tag[p]) {
          for (i32 i = L[p]; i <= R[p]; ++i) a[i] = tag[p];
          tag[p] = 0;
        }
        for (i32 i = l; i <= r; ++i) a[i] = v;
        for (i32 i = L[p]; i <= R[p]; ++i) sum[p][i - L[p] + 1] = sum[p][i - L[p]] + a[i];
        for (i32 i = p + 1; i <= bel[n]; ++i) {
          if (!tag[i - 1]) pre[i] = pre[i - 1] + sum[i - 1][R[i - 1] - L[i - 1] + 1];
          else pre[i] = pre[i - 1] + (R[i - 1] - L[i - 1] + 1) * tag[i - 1];
        }
      } else {
        if (tag[p]) {
          for (i32 i = L[p]; i <= R[p]; ++i) a[i] = tag[p];
          tag[p] = 0;
        }
        for (i32 i = l; i <= R[p]; ++i) a[i] = v;
        if (tag[q]) {
          for (i32 i = L[q]; i <= R[q]; ++i) a[i] = tag[q];
          tag[q] = 0;
        }
        for (i32 i = L[q]; i <= r; ++i) a[i] = v;
        for (i32 i = L[p]; i <= R[p]; ++i) sum[p][i - L[p] + 1] = sum[p][i - L[p]] + a[i];
        for (i32 i = L[q]; i <= R[q]; ++i) sum[q][i - L[q] + 1] = sum[q][i - L[q]] + a[i];
        for (i32 i = p + 1; i < q; ++i) tag[i] = v;
        for (i32 i = p + 1; i <= bel[n]; ++i) {
          if (!tag[i - 1]) pre[i] = pre[i - 1] + sum[i - 1][R[i - 1] - L[i - 1] + 1];
          else pre[i] = pre[i - 1] + (R[i - 1] - L[i - 1] + 1) * tag[i - 1];
        }
      }
      return void();
    }
    i32 query(i32 x) {
      if (tag[bel[x]])
        return pre[bel[x] - 1] + tag[bel[x]] * (x - L[bel[x]] + 1);
      return pre[bel[x] - 1] + sum[bel[x]][x - L[bel[x]] + 1];
    }
  }
  struct blk2 {
    i32 bel[N], L[N], R[N];
    i32 t[N], st1[N][B + 5], st2[N][B + 5], pre1[M], pre2[M];
    void rebuild() {
      for (i32 i = 1; i <= bel[n]; ++i) {
        pre1[i] = pre1[i - 1] + st1[i - 1][R[i] - L[i] + 1];
        pre2[i] = pre2[i - 1] + st2[i - 1][R[i] - L[i] + 1];
      }
      return void();
    }
    void init(i32 l, i32 r) {
      for (i32 i = l; i <= r; ++i) ++t[b[i]];
      for (i32 i = 1; i <= bel[n]; ++i)
        for (i32 j = L[i]; j <= R[i]; ++j) {
          st1[i][j - L[i] + 1] = st1[i][j - L[i]] + t[j];
          st2[i][j - L[i] + 1] = st2[i][j - L[i]] + t[j] * j;
        }
      rebuild();
      return void();
    }
    void modify(i32 p, i32 q, i32 c) {
      t[p] -= c, t[q] += c;
      for (i32 i = p; i <= R[bel[p]]; ++i) {
        st1[bel[p]][i - L[i] + 1] -= c;
        st2[bel[q]][i - L[i] + 1] -= c * p;
      }
      for (i32 i = q; i <= R[bel[q]]; ++i) {
        st1[bel[p]][i - L[i] + 1] += c;
        st2[bel[q]][i - L[i] + 1] += c * q;
      }
      rebuild();
      return void();
    }
    i32 query1(i32 x) { return pre1[bel[x]] + st1[bel[x]][x - L[bel[x]] + 1]; }
    i32 query2(i32 x) { return pre2[bel[x]] + st2[bel[x]][x - L[bel[x]] + 1]; }
  };
  struct ODT {
    struct node {
      i32 l, r;
      mutable i32 v;
      node() = default;
      node(i32 _l, i32 _r, i32 _v): l(_l), r(_r), v(_v) {}
      bool operator <(const node &other) const { return this->l < other.l; }
    };
    std::set<node> odt;
    auto split(i32 p) {
      if (p > n) return odt.end();
      auto it = --odt.upper_bound(node(p, 0, 0));
      if (it->l == p) return it;
      auto l = it->l, r = it->r, v = it->v;
      odt.erase(it);
      odt.ep(l, p - 1, v);
      return odt.insert(node(p, r, v)).first;
    }
    void assign(i32 l, i32 r, i32 v) {
      auto it2 = split(r + 1), it1 = split(l);
      odt.erase(it1, it2);
      odt.ep(l, r, v);
      return void();
    }
    void ato1(i32 l, i32 r);
    void ato2(i32 l, i32 r, i32 v);
    void ato3(i32 l, i32 r, i32 v, i32 p);
  } t1;
  namespace blk3 {
    // O(sqrtn) modify ans
    // O(sqrtn) query ans
    // O(sqrtn) modify st1 st2
    i32 ans[M], tag[M];
    blk2 blk[M]; ODT tree[M];
    void init() {
      for (i32 i = 1; i <= bel[n]; ++i) ans[i] = 0;
      for (i32 i = 1; i <= bel[n]; ++i)
        for (i32 j = L[i]; j <= R[i]; ++j)
          tree[i].odt.ep(j, j, b[j]);
      return void();
    }
    void modify(i32 c, i32 v, i32 op) {
      for (i32 i = 1; i <= bel[n]; ++i) {
        if (tag[i]) continue;
        i32 t1 = blk[i].query1(c);
        i32 t2 = blk[i].query2(c);
        ans[i] += op * v * (t2 + (n - t1) * c);
      }
      return void();
    }
    void change(i32 l, i32 r, i32 v) {
      i32 p = bel[l], q = bel[r];
      if (p == q) {
        if (tag[p]) {
          tree[p].ato3(L[p], R[p], tag[p], p);
          tree[p].assign(l, r, v);
          tag[p] = 0;
        }
        for (i32 i = l; i <= r; ++i) {
          tree[p].ato3(l, r, v, p);
          tree[p].assign(l, r, v);
        }
      } else {
        if (tag[p]) {
          tree[p].ato3(L[p], R[p], tag[p], p);
          tree[p].assign(l, r, v);
          tag[p] = 0;
        }
        if (tag[q]) {
          tree[q].ato3(L[q], R[q], tag[q], q);
          tree[q].assign(l, r, v);
          tag[q] = 0;
        }
        for (i32 i = l; i <= R[p]; ++i) {
          tree[p].ato3(l, R[p], v, p);
          tree[p].assign(l, R[p], v);
        }
        for (i32 i = L[q]; i <= r; ++i) {
          tree[q].ato3(L[q], r, v, q);
          tree[q].assign(L[q], r, v);
        }
        for (i32 i = p + 1; i < q; ++i) tag[i] = v;
      }
      return void();
    }
    i32 query(i32 l, i32 r) {
      i32 p = bel[l], q = bel[r];
      i32 ret = 0;
      if (p == q) {
        for (i32 i = l; i <= r; ++i)
          ret += blk1::query(b[i]);
      } else {
        for (i32 i = l; i <= R[p]; ++i) ret += blk1::query(b[i]);
        for (i32 i = L[q]; i <= r; ++i) ret += blk1::query(b[i]);
        for (i32 i = p + 1; i < q; ++i) {
          if (tag[i]) ret += blk1::query(tag[i]) * (R[i] - L[i] + 1);
          else ret += ans[i];
        }
      }
      return ret;
    }
  }
  void ODT::ato1(i32 l, i32 r) {
    auto it2 = split(r + 1), it1 = split(l);
    for (auto it = it1; it != it2; ++it)
      blk3::modify(it->l - 1, it->v, 1), blk3::modify(it->r, it->v, -1);
    return void();
  }
  void ODT::ato2(i32 l, i32 r, i32 v) {
    auto it2 = split(r + 1), it1 = split(l);
    for (auto it = it1; it != it2; ++it)
      blk3::modify(it->l - 1, v, -1), blk3::modify(it->r, v, 1);
    return void();
  }
  void ODT::ato3(i32 l, i32 r, i32 v, i32 p) {
    auto it2 = split(r + 1), it1 = split(l);
    for (auto it = it1; it != it2; ++it)
      blk3::blk[p].modify(it->v, v, it->r - it->l + 1);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) b[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) {
      bel[i] = (i - 1) / B + 1;
      if (!L[bel[i]]) L[bel[i]] = i;
      R[bel[i]] = i;
    }
    blk1::init();
    blk3::init();
    for (i32 i = 1; i <= n; ++i) t1.odt.ep(i, i, a[i]);
    for (i32 i = 1; i <= m; ++i) {
      static i32 op, l, r, v;
      op = read(), l = read(), r = read();
      if (op != 3) v = read();
      if (op == 1) {
        blk1::modify(l, r, v);
        t1.ato1(l, r), t1.ato2(l, r, v);
        t1.assign(l, r, v);
      }
      if (op == 2) {
        blk3::change(l, r, v);
      }
      if (op == 3) {
        fprintf(fout, "%d\n", blk3::query(l, r));
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P7983::main(), 0; }
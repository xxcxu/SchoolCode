#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()
FILE *fin, *fout, *ferr;
i32 read() {
  i32 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_HLP1437 {
  bool _1;
  static const i32 N = 300005;
  i32 n, m;
  i32 a[N], pre[N], nxt[N];
  bool _2;
  template<const i32 N, const i32 M>
  struct mat {
    i64 a[N][M];
    mat() { std::memset(a, 0, sizeof a); }
    const i64* operator [](const i32 x) const { return a[x]; }
    i64* operator [](i32 x) { return a[x]; }
    template<const i32 K>
    mat<N, K> operator *(const mat<M, K> &other) {
      mat<N, K> ret;
      for (i32 i = 0; i < N; ++i)
        for (i32 j = 0; j < K; ++j)
          for (i32 k = 0; k < M; ++k)
            ret[i][j] += this->a[i][k] * other[k][j];
      return ret;
    }
    void print() {
      for (i32 i = 0; i < N; ++i)
        for (i32 j = 0; j < M; ++j)
          fprintf(fout, "%lld%c", this->a[i][j], " \n"[j == M - 1]);
      return void();
    }
  };
  mat<3, 3> htag;
  void reset(mat<3, 3> &v) {
    v[0][0] = 1, v[0][1] = 0, v[0][2] = 0;
    v[1][0] = 0, v[1][1] = 1, v[1][2] = 0;
    v[2][0] = 0, v[2][1] = 0, v[2][2] = 1;
    return void();
  }
  bool value(const mat<3, 3> &v) {
    for (i32 i = 0; i < 3; ++i)
      for (i32 j = 0; j < 3; ++j) {
        if (i == j) if (v[i][j] != 1) return true;
        if (i != j) if (v[i][j] != 0) return true;
      }
    return false;
  }
  const mat<3, 3> make_mat(i32 v) {
    mat<3, 3> ret;
    ret[0][0] = 1;
    ret[2][1] = v;
    ret[2][2] = 1;
    return ret;
  }
  void init() {
    htag[0][0] = 1;
    htag[1][0] = 1;
    htag[1][1] = 1;
    htag[2][2] = 1;
    return void();
  }
  struct SegmentTree {
    struct TreeNode {
      mat<1, 3> v;
      mat<3, 3> tag;
      i32 max, lazy_tag;
    } tr[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) {
      tr[x].v[0][0] = tr[ls].v[0][0] + tr[rs].v[0][0];
      tr[x].v[0][1] = tr[ls].v[0][1] + tr[rs].v[0][1];
      tr[x].v[0][2] = tr[ls].v[0][2] + tr[rs].v[0][2];
      tr[x].max = std::max(tr[ls].max, tr[rs].max);
      return void();
    }
    void pushtag(i32 x, i32 v) {
      tr[x].v = tr[x].v * make_mat(v);
      tr[x].tag = tr[x].tag * make_mat(v);
      return void();
    }
    void pushtag(i32 x, const mat<3, 3> &v) {
      tr[x].v = tr[x].v * v;
      tr[x].tag = tr[x].tag * v;
      return void();
    }
    void pushtag2(i32 x, i32 v) {
      tr[x].max = v;
      tr[x].lazy_tag = v;
      return void();
    }
    void pushdown(i32 x) {
      if (value(tr[x].tag)) {
        pushtag(ls, tr[x].tag);
        pushtag(rs, tr[x].tag);
        reset(tr[x].tag);
      }
      if (tr[x].lazy_tag) {
        pushtag2(ls, tr[x].lazy_tag);
        pushtag2(rs, tr[x].lazy_tag);
        tr[x].lazy_tag = 0;
      }
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      reset(tr[x].tag);
      tr[x].v[0][2] = 1;
      tr[x].max = 0, tr[x].lazy_tag = 0;
      if (l == r) return void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    i32 query_pos(i32 x, i32 l, i32 r, i32 v) {
      if (tr[x].max <= v) return 0;
      if (l == r) return l;
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (tr[rs].max < v) return query_pos(ls, l, mid, v);
      else return query_pos(rs, mid + 1, r, v); 
    }
    void assign(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql <= l && r <= qr) {
        pushtag(x, v);
        pushtag2(x, v);
        return void();
      }
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (ql <= mid) assign(ls, l, mid, ql, qr, v);
      if (qr > mid) assign(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) {
        pushtag(x, htag);
        return void();
      }
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (ql <= mid) modify(ls, l, mid, ql, qr);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr);
      return pushup(x);
    }
    i32 query1(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x].max;
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (p <= mid) return query1(ls, l, mid, p);
      else return query1(rs, mid + 1, r, p);
    }
    i64 query2(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x].v[0][1];
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (p <= mid) return query2(ls, l, mid, p);
      else return query2(rs, mid + 1, r, p);
    }
    i64 query3(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x].v[0][0];
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (p <= mid) return query3(ls, l, mid, p);
      else return query3(rs, mid + 1, r, p);
    }
    i64 query4(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x].v[0][2];
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (p <= mid) return query4(ls, l, mid, p);
      else return query4(rs, mid + 1, r, p);
    }
    i64 query_hsum(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr)
        return tr[x].v[0][0];
      pushdown(x);
      i32 mid((l + r) >> 1);
      i64 hsum = 0;
      if (ql <= mid) hsum += query_hsum(ls, l, mid, ql, qr);
      if (qr > mid) hsum += query_hsum(rs, mid + 1, r, ql, qr);
      return hsum;
    }
  } seg;
  std::vector<std::pair<i32, i32>> qu[N];
  i64 ans[N];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("seq.in", "r");
    fout = fopen("seq.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) if (!pre[a[i]]) pre[a[i]] = i;
    for (i32 i = 1; i <= n; ++i) nxt[a[i]] = i;
    for (i32 i = 1; i <= m; ++i) {
      static i32 l, r;
      l = read(), r = read();
      qu[r].eb(l, i);
    }
    seg.build(1, 1, n);
    init();
    for (i32 i = 1; i <= n; ++i) {
      if (nxt[a[i]] == i) {
        i32 p = seg.query_pos(1, 1, n, a[i]);
        if (p + 1 <= pre[a[i]])
          seg.assign(1, 1, n, p + 1, pre[a[i]], a[i]);
      }
      seg.modify(1, 1, n, 1, n);
      for (auto &[l, id] : qu[i])
        ans[id] = seg.query_hsum(1, 1, n, l, i);
    }
    for (i32 i = 1; i <= m; ++i) fprintf(fout, "%lld\n", ans[i]);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1437::main(), 0; }
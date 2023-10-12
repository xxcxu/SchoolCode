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
namespace Solution_Of_CF280D {
  bool _1;
#pragma endregion
  static const i32 N = 100005;
  i32 n, top;
  i32 a[N]; std::tuple<i32, i32> st[N];
  namespace SegmentTree {
    template<const bool (*compare)(i32 x, i32 y)>
    struct Node {
      i32 sum;
      i32 lmax, rmax;
      i32 lpos, rpos;
      i32 max, l, r;
      Node() = default;
      Node(i32 p, i32 v): sum(v), lmax(v), rmax(v), max(v), lpos(p), rpos(p), l(p), r(p) {}
      Node(i32 _sum, i32 _lmax, i32 _rmax, i32 _lpos, i32 _rpos, i32 _max, i32 _l, i32 _r):
        sum(_sum), lmax(_lmax), rmax(_rmax), lpos(_lpos), rpos(_rpos), max(_max), l(_l), r(_r) {}
      Node operator +(const Node &other) const {
        Node ret = Node();
        ret.sum = this->sum + other.sum;
        if (compare(this->sum + other.lmax, this->lmax)) {
          ret.lpos = other.lpos;
          ret.lmax = this->sum + other.lmax;
        } else {
          ret.lpos = this->lpos;
          ret.lmax = this->lmax;
        }
        if (compare(other.sum + this->rmax, other.rmax)) {
          ret.rpos = this->rpos;
          ret.rmax = other.sum + this->rmax;
        } else {
          ret.rpos = other.rpos;
          ret.rmax = other.rmax;
        }
        if (compare(this->max, other.max)) {
          ret.max = this->max;
          ret.l = this->l;
          ret.r = this->r;
        } else {
          ret.max = other.max;
          ret.l = other.l;
          ret.r = other.r;
        }
        if (compare(this->rmax + other.lmax, ret.max)) {
          ret.max = this->rmax + other.lmax;
          ret.l = this->rpos;
          ret.r = other.lpos;
        }
        return ret;
      }
      void rev() {
        this->sum *= -1, this->max *=- 1;
        this->lmax *= -1, this->rmax *= -1;
        return void();
      }
    };
    template<const bool (*compare1)(i32 x, i32 y), const bool (*compare2)(i32 x, i32 y)>
    auto copy(Node<compare1> &a) { return Node<compare2>(a.sum, a.lmax, a.rmax, a.lpos, a.rpos, a.max, a.l, a.r); }
    template<const bool (*compare1)(i32 x, i32 y), const bool (*compare2)(i32 x, i32 y)>
    void swap(Node<compare1> &a, Node<compare2> &b) {
      auto t = copy<compare1, compare2>(a);
      a = copy<compare2, compare1>(b);
      b = t;
      return void();
    }
    const bool mybig(i32 x, i32 y) { return x > y; }
    const bool mysml(i32 x, i32 y) { return x < y; }
    struct TreeNode {
      Node<mybig> n1;
      Node<mysml> n2;
      TreeNode() = default;
      TreeNode(i32 p, i32 v) { n1 = Node<mybig>(p, v); n2 = Node<mysml>(p, v); }
      TreeNode operator +(const TreeNode &other) const {
        TreeNode ret = TreeNode();
        ret.n1 = this->n1 + other.n1;
        ret.n2 = this->n2 + other.n2;
        return ret;
      }
    } tr[N << 2];
    bool rev[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) {
      tr[x] = tr[ls] + tr[rs];
      return void();
    }
    void pushtag(i32 x) {
      rev[x] ^= 1;
      tr[x].n1.rev(), tr[x].n2.rev();
      swap(tr[x].n1, tr[x].n2);
      return void();
    }
    void pushdown(i32 x) {
      if (rev[x]) {
        pushtag(ls);
        pushtag(rs);
        rev[x] = 0;
      }
      return void();
    } 
    void build(i32 x, i32 l, i32 r) {
      if (l == r)
        return tr[x] = TreeNode(l, a[l]), void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    void change(i32 x, i32 l, i32 r, i32 p, i32 v) {
      if (l == r)
        return tr[x] = TreeNode(p, v), void();
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (p <= mid) change(ls, l, mid, p, v);
      else change(rs, mid + 1, r, p, v);
      return pushup(x);
    }
    void reverse(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return pushtag(x);
      pushdown(x);
      i32 mid((l + r) >> 1);
      if (ql <= mid) reverse(ls, l, mid, ql, qr);
      if (qr > mid) reverse(rs, mid + 1, r, ql, qr);
      return pushup(x);
    }
    auto query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return tr[x].n1;
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (ql > mid) return query(rs, mid + 1, r, ql, qr);
      if (qr <= mid) return query(ls, l, mid, ql, qr);
      return query(ls, l, mid, ql, qr) + query(rs, mid + 1, r, ql, qr);
    }
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    i32 m = read();
    SegmentTree::build(1, 1, n);
    while (m--) {
      static i32 op, l, r, k;
      op = read(), l = read(), r = read();
      if (op == 0) {
        SegmentTree::change(1, 1, n, l, r);
      } else {
        k = read();
        i32 ans = 0, sum = 0;
        while (k--) {
          auto node = SegmentTree::query(1, 1, n, l, r);
          ans = std::max(ans, sum += node.max);
          SegmentTree::reverse(1, 1, n, node.l, node.r);
          st[++top] = std::make_tuple(node.l, node.r);
        }
        while (top) {
          auto& [nl, nr] = st[top--];
          SegmentTree::reverse(1, 1, n, nl, nr);
        }
        fprintf(fout, "%d\n", ans);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF280D::main(), 0; }
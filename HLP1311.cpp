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
#include<cstdio>
#include<algorithm>
#include<set>
#include<map> 
#define SNI set <nod> :: iterator 
#define SDI set <data> :: iterator 
using namespace std;const int N=1e5+10;int n;int m;int pre[N];int npre[N];int a[N];int tp[N];int lf[N];int rt[N];int co[N];
struct modi{int t;int pos;int pre;int va;friend bool operator <(modi a,modi b){return a.pre<b.pre;}}md[10*N];int tp1;
struct qry{int t;int l;int r;int ans;friend bool operator <(qry a,qry b){return a.l<b.l;}}qr[N];int tp2;int cnt;
inline bool cmp(const qry& a,const qry& b){return a.t<b.t;}
inline void modify(int pos,int co)//修改函数
{
	if(npre[pos]==co)return;
  md[++tp1]=(modi){++cnt,pos,npre[pos],-1};
	md[++tp1]=(modi){++cnt,pos,npre[pos]=co,1};
}
namespace prew
{
	int lst[2*N];map <int,int> mp;//提前离散化
	inline void prew()
	{
		scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),mp[a[i]]=1;
		for(int i=1;i<=m;i++){
      scanf("%d%d%d",&tp[i],&lf[i],&rt[i]);
      if(tp[i]==1)scanf("%d",&co[i]),mp[co[i]]=1;
    }
		map <int,int> :: iterator it,it1;
		for(it=mp.begin(),it1=it,++it1;it1!=mp.end();++it,++it1) it1->second+=it->second;
		for(int i=1;i<=n;i++)a[i]=mp[a[i]];
    for(int i=1;i<=m;i++)if(tp[i]==1)co[i]=mp[co[i]];
		for(int i=1;i<=n;i++)pre[i]=lst[a[i]],lst[a[i]]=i;
    for(int i=1;i<=n;i++)npre[i]=pre[i];
	}
}
namespace colist
{
    struct Node {
      int32 l, r, x;
      Node() = default;
      Node(int32 l, int32 r, int32 x = 0):
        l(l), r(r), x(x) {}
      bool operator <(const Node &other) const { return this->r < other.r; }
    };
    std::set<Node> s, c[N * 2], bd;
    void split(int32 p) {
      auto it = s.lower_bound(Node(0, p, 0));
      auto dat = *it;
      if (p == dat.r) return void();
      s.erase(dat), c[dat.x].erase(dat);
      s.ep(dat.l, p, dat.x), c[dat.x].ep(dat.l, p, dat.x);
      s.ep(p + 1, dat.r, dat.x), c[dat.x].ep(p + 1, dat.r, dat.x);
      return void();
    }
    void del(auto it) {
      bd.ep(it->l);
      auto it1, it2;
      it1 = it2 = c[it->x].find(*it);
      ++it2;
      if (it2 != c[it->x].end()) bd.ep(it2->l);
      s.erase(it);
      c[it->x].erase(it1);
      return void();
    }
    void ins(Node v) {
      
    }
    inline void ins(data p)//插入一个节点
    {
      s.insert(p);SNI it=c[p.x].insert((nod){p.l,p.r}).first;++it;
      if(it!=c[p.x].end()){bd.insert(it->l);}
    }
    inline void stv(int l,int r,int x)//区间赋值
    {
      if(l!=1) split(l-1);split(r);
      int p=l;//split两下之后删掉所有区间
      while(p!=r+1){SDI it=s.lower_bound((data){0,p,0});p=it->r+1;del(it);}
      ins((data){l,r,x});//扫一遍set处理所有变化的pre值
      for(set <int> :: iterator it=bd.begin();it!=bd.end();++it)
      {
        SDI it1=s.lower_bound((data){0,*it,0});
        if(*it!=it1->l)modify(*it,*it-1);
        else
        {
          SNI it2=c[it1->x].lower_bound((nod){0,*it});
          if(it2!=c[it1->x].begin())--it2,modify(*it,it2->r);else modify(*it,0);
        }
      }bd.clear();
    }
    inline void ih()
    {
      int nc=a[1];int ccnt=1;//将连续的一段插入到set中
      for(int i=2;i<=n;i++)
        if(nc!=a[i]) {
          s.insert((data){i-ccnt,i-1,nc});
          c[nc].insert((nod){i-ccnt,i-1});
          nc=a[i];ccnt=1;
        }
        else ccnt++;
        s.insert((data){n-ccnt+1,n,a[n]});
        c[a[n]].insert((nod){n-ccnt+1,n});
    }
  }
  namespace cdq
  {   
    struct treearray//树状数组
    {
        int ta[N];
        inline void c(int x,int t){for(;x<=n;x+=x&(-x))ta[x]+=t;}
        inline void d(int x){for(;x<=n;x+=x&(-x))ta[x]=0;}
        inline int  q(int x){int r=0;for(;x;x-=x&(-x))r+=ta[x];return r;}
        inline void clear(){for(int i=1;i<=n;i++)ta[i]=0;}
    }ta;int srt[N];
    inline bool cmp1(const int& a,const int& b){return pre[a]<pre[b];}
    inline void solve(int l1,int r1,int l2,int r2,int L,int R)//cdq
    {
        if(l1==r1||l2==r2)return;int mid=(L+R)/2;
        int mid1=l1;while(mid1!=r1&&md[mid1+1].t<=mid)mid1++;
        int mid2=l2;while(mid2!=r2&&qr[mid2+1].t<=mid)mid2++;
        solve(l1,mid1,l2,mid2,L,mid);solve(mid1,r1,mid2,r2,mid,R);
        if(l1!=mid1&&mid2!=r2)
        {
            sort(md+l1+1,md+mid1+1);sort(qr+mid2+1,qr+r2+1);
            for(int i=mid2+1,j=l1+1;i<=r2;i++)//考虑左侧对右侧贡献
            {
                while(j<=mid1&&md[j].pre<qr[i].l)ta.c(md[j].pos,md[j].va),j++;
                qr[i].ans+=ta.q(qr[i].r)-ta.q(qr[i].l-1);
            }for(int i=l1+1;i<=mid1;i++)ta.d(md[i].pos);
        }
    }
	inline void mainsolve()
	{
		colist::ih();for(int i=1;i<=m;i++)
			if(tp[i]==1)colist::stv(lf[i],rt[i],co[i]);else qr[++tp2]=(qry){++cnt,lf[i],rt[i],0};
		sort(qr+1,qr+tp2+1);for(int i=1;i<=n;i++)srt[i]=i;sort(srt+1,srt+n+1,cmp1);
		for(int i=1,j=1;i<=tp2;i++)//初始化一下每个询问的值
		{
			while(j<=n&&pre[srt[j]]<qr[i].l)ta.c(srt[j],1),j++;
			qr[i].ans+=ta.q(qr[i].r)-ta.q(qr[i].l-1);
		}ta.clear();sort(qr+1,qr+tp2+1,cmp);solve(0,tp1,0,tp2,0,cnt);sort(qr+1,qr+tp2+1,cmp);
		for(int i=1;i<=tp2;i++)printf("%d\n",qr[i].ans);
	}
}
int main(){prew::prew();cdq::mainsolve();return 0;}//拜拜程序~
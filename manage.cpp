#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mkp make_pair
using namespace std;
const int inf=2147483647,N=5e5+5;
inline int rd(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,m,lst[N],pre[N],ret[N],a[N];
namespace S{
	int f[N<<2];
	#define ls (x<<1)
	#define rs ((x<<1)|1)
	void add(int x,int l,int r,int pos,int val){
		if(l==r){
			f[x]+=val;
			return ;
		}
		int mid=l+r>>1;
		if(mid>=pos) add(ls,l,mid,pos,val);
		else add(rs,mid+1,r,pos,val);
		f[x]=f[ls]+f[rs];
	}
	int ask(int x,int l,int r,int a,int b){
		if(l>=a&&r<=b) return f[x];
		int mid=l+r>>1,ret=0;
		if(mid>=a) ret+=ask(ls,l,mid,a,b);
		if(mid<b) ret+=ask(rs,mid+1,r,a,b);
		return ret;
	}
}
signed main(){
	freopen("manage.in","r",stdin);
	freopen("manage.out","w",stdout);
	m=rd(),n=rd();
	for(int i=1;i<=n;i++){
		a[i]=rd();
		S::add(1,1,n,i,1);
		if(lst[a[i]]) S::add(1,1,n,lst[a[i]],-1);
		pre[i]=lst[a[i]];
		lst[a[i]]=i;
		int t=S::ask(1,1,n,pre[i]+1,n);
		if(pre[i]) ret[t-1]++;
		else ret[m]++;
	}
	for(int i=m;i;i--) ret[i]+=ret[i+1];
	for(int i=1;i<=m;i++) printf("%lld ",ret[i]);
    return 0;
}
/*
4 6
2 1 2 2 1 4
*/




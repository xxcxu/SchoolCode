#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define pb push_back
using namespace std;
const int N=5e6+100;
int n;
char s[N],t[N];
vector<pii>pos;
int check(int k)
{
	memcpy(t,s,sizeof(t));
	for(int i=0;i<pos.size();i++)for(int j=pos[i].fi-1;j>=pos[i].fi-k;j--)t[j]='1';
	if(t[1]=='0'&&t[2]=='1')return 0;
	if(t[n-k]=='0'&&t[n-k-1]=='1')return 0;
	for(int i=1;i<=n-k;i++)if(t[i]=='0')
	{
		int j=i;while(j<=n-k&&t[j+1]=='0')j++;
		j--;if(i!=1)i++;
		if(i>j)continue;
		while(j-i+1>=3)t[i]='1',i+=2;
		if(j-i+1==2){if(k==1)return 0;t[i]=t[i+1]='1';}
		else t[i]='1';
		i=j+2;
	}
	for(int i=1;i<n-k;i++)if(t[i]=='0'&&t[i+1]=='0')return 0;
	return 1;
}
void write(char*t){puts("Yes");for(int i=1;i<=n;i++)putchar(t[i]=='1'?'B':'R');}
signed main()
{
	freopen("soccer.in","r",stdin);
	freopen("soccer.out","w",stdout);
	scanf("%d%s",&n,s+1);
	int mn=0,mx=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='0')continue;
		int j=i;while(j<n&&s[j+1]=='1')j++;
		pos.push_back(mk(i,j));
		i=j+1;
	}
	if(!pos.size())return write(s),0;
	mn=3;
	for(int i=1;i<pos.size();i++) mn=min(mn,pos[i].fi-pos[i-1].se-2),mx=max(mx,pos[i].fi-pos[i-1].se-2);
	mn=min(mn,pos[0].fi-1);mn=min(mn,n-pos.back().se);
	mx=max(mx,pos[0].fi-1);mx=max(mx,n-pos.back().se);
	if(!mx)return write(s),0;
	if(mn>=1&&check(1))return write(t),0;
	if(mn>=2&&check(2))return write(t),0;
	if(mn>=3&&check(3))return write(t),0;
	puts("No");
	return 0;
}
/*
8
11101111
*/
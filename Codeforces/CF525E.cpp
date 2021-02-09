#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=25+5;
const ll fac[]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000};

int n,k;
ll s;
int a[MAXN];
unordered_map<ll,ll> M[MAXN];

inline void dfs1(reg int dep,ll sum,reg int res){
	if(sum>s||res<0)
		return;
	if(dep>(n+1)/2){
		++M[k-res][sum];
		return;
	}
	dfs1(dep+1,sum,res);
	dfs1(dep+1,sum+a[dep],res);
	if(a[dep]<19) dfs1(dep+1,sum+fac[a[dep]],res-1);
	return;
}

ll ans;

inline void dfs2(reg int dep,reg ll sum,reg int res){
	if(sum>s||res<0)
		return;
	if(dep>n){
		for(reg int i=0;i<=res;++i)
			if(M[i].find(s-sum)!=M[i].end())
				ans+=M[i][s-sum];
		return;
	}
	dfs2(dep+1,sum,res);
	dfs2(dep+1,sum+a[dep],res);
	if(a[dep]<19) dfs2(dep+1,sum+fac[a[dep]],res-1);
	return;
}

int main(void){
	n=read(),k=read(),s=readll();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	dfs1(1,0,k);
	dfs2((n+1)/2+1,0,k);
	printf("%lld\n",ans);
	return 0;
}
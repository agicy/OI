#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,k;
int a[MAXN];
ll dp[2][MAXN];
int T[MAXN];

int l=1,r=0;
ll cost;

inline void add(reg int x){
	cost+=T[x]++;
	return;
}

inline void del(reg int x){
	cost-=--T[x];
	return;
}

inline ll getVal(reg int L,reg int R){
	while(l<L) del(a[l++]);
	while(l>L) add(a[--l]);
	while(r<R) add(a[++r]);
	while(r>R) del(a[r--]);
	return cost;
}

inline void solve(reg ll f[],reg int L,reg int R,reg ll g[],reg int l,reg int r){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			f[i]=g[l-1]+getVal(l,i);
		return;
	}
	reg int mid=(L+R)>>1,ptr=1;
	for(reg int i=l;i<=min(r,mid);++i)
		if(f[mid]>g[i-1]+getVal(i,mid))
			ptr=i,f[mid]=g[i-1]+getVal(i,mid);
	solve(f,L,mid-1,g,l,ptr),solve(f,mid+1,R,g,ptr,r);
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(reg int j=1;j<=k;++j){
		memset(dp[j&1],0x3f,sizeof(dp[j&1]));
		solve(dp[j&1],1,n,dp[(j&1)^1],1,n);
	}
	printf("%lld\n",dp[k&1][n]);
	return 0;
}
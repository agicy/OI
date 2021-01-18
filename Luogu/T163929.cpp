#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;

int n,m;
int a[MAXN],b[MAXN];
int suma[MAXN],sumb[MAXN];
ll preW[MAXN];

inline ll getVal(reg int l,reg int r){
	return (r-l+1ll)*(preW[r]-preW[l-1]-1ll*suma[l-1]*(sumb[r]-sumb[l-1]));
}

ll dp[2][MAXN];

inline void solve(reg ll f[],reg int L,reg int R,reg ll g[],reg int l,reg int r){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			f[i]=g[l-1]+getVal(l,i);
		return;
	}
	reg int mid=(L+R)>>1,ptr=l;
	for(reg int i=l;i<=min(r,mid);++i)
		if(f[mid]>g[i-1]+getVal(i,mid))
			ptr=i,f[mid]=g[i-1]+getVal(i,mid);
	solve(f,L,mid-1,g,l,ptr),solve(f,mid+1,R,g,ptr,r);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),suma[i]=suma[i-1]+a[i];
	for(reg int i=1;i<=n;++i)
		b[i]=read(),sumb[i]=sumb[i-1]+b[i];
	reg int sa=0,sb=0;
	for(reg int i=1;i<=n;++i){
		preW[i]=preW[i-1]+1ll*sa*b[i];
		sa+=a[i],sb+=b[i];
	}
	m=read();
	memset(dp[0],0x3f,sizeof(dp[0]));
	dp[0][0]=0;
	for(reg int i=1;i<=m;++i){
		memset(dp[i&1],0x3f,sizeof(dp[i&1]));
		solve(dp[i&1],1,n,dp[(i&1)^1],1,n);
		writeln(dp[i&1][n]);
	}
	flush();
	return 0;
}
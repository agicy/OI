#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=10000000+5;

int n,m;
bool vis[MAXN];
int mu[MAXN];
int cnt,prime[MAXN];
ll g[MAXN],sum[MAXN];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			mu[i]=-1,prime[++cnt]=i;
		for(reg int j=1;j<=cnt&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=cnt&&i*prime[j]<=n;++j)
			g[i*prime[j]]+=mu[i];
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+g[i];
	return;
}

int main(void){
	Init(1e7);
	reg int T=read();
	while(T--){
		n=read(),m=read();
		reg ll ans=0;
		for(reg int l=1,r,S=min(n,m);l<=S;l=r+1){
			r=min(n/(n/l),m/(m/l));
			ans+=(ll)(n/l)*(m/l)*(sum[r]-sum[l-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
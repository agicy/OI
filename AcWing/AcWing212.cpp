#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int mod=1e9+9;

int n;
bool vis[MAXN];
int p[MAXN],f[MAXN],fac[MAXN],L[MAXN];

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int dfs(reg int u){
	vis[u]=true;
	if(vis[p[u]])
		return 1;
	else
		return dfs(p[u])+1;
}

int main(void){
	reg int T=read();
	fac[0]=1;
	for(reg int i=1;i<MAXN;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	f[1]=1;
	for(reg int i=2;i<MAXN;++i)
		f[i]=fpow(i,i-2);
	while(T--){
		memset(vis,false,sizeof(vis));
		n=read();
		for(reg int i=1;i<=n;++i)
			p[i]=read();
		reg int cnt=0;
		for(reg int i=1;i<=n;++i)
			if(!vis[i])
				L[++cnt]=dfs(i);
		reg int ans=fac[n-cnt];
		for(reg int i=1;i<=cnt;++i)
			ans=1ll*ans*f[L[i]]%mod*fpow(fac[L[i]-1],mod-2)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
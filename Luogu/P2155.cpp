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

const int MAXN=1e7+5;

int mod;
bool vis[MAXN];
int tot,prime[MAXN];
int sum[MAXN];
int pod[MAXN],inv[MAXN];
int invpod[MAXN],fac[MAXN];

inline void Init(reg int n){
	vis[0]=vis[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	inv[1]=1;
	for(int i=2;i<mod&&i<=n;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	pod[0]=1;
	for(reg int i=1;i<=tot;++i)
		pod[i]=1ll*pod[i-1]*(prime[i]-1)%mod;
	invpod[0]=1;
	for(reg int i=1;i<=tot;++i)
		if(prime[i]!=mod)
			invpod[i]=1ll*invpod[i-1]*inv[prime[i]%mod]%mod;
		else
			invpod[i]=invpod[i-1];
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		if(i!=mod)
			fac[i]=1ll*fac[i-1]*i%mod;
		else
			fac[i]=fac[i-1];
	for(reg int i=2;i<=n;++i)
		if(vis[i])
			sum[i]=sum[i-1];
		else
			sum[i]=sum[i-1]+1;
	return;
}

int main(void){
	reg int T=read();
	mod=read();
	Init(1e7);
	while(T--){
		reg int n=read(),m=read();
		if(n>=mod&&m<mod)
			puts("0");
		else
			printf("%lld\n",1ll*fac[n]*pod[sum[m]]%mod*invpod[sum[m]]%mod);
	}
	return 0;
}
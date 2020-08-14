#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

const int MAXN=10000000+5;

bool vis[MAXN];
int cnt,prime[MAXN];
int mu[MAXN],phi[MAXN];
ll Smu[MAXN],Sphi[MAXN];
map<int,ll> MSmu,MSphi;

uint S=1e6;

inline void Init(void){
	mu[1]=phi[1]=1;
	for(reg uint i=2;i<=S;++i){
		if(!vis[i]){
			mu[i]=-1;
			phi[i]=i-1;
			prime[++cnt]=i;
		}
		for(reg int j=1;j<=cnt&&i*prime[j]<=S;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			mu[i*prime[j]]=-mu[i];
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(reg uint i=1;i<=S;++i){
		Smu[i]=Smu[i-1]+mu[i];
		Sphi[i]=Sphi[i-1]+phi[i];
	}
	return;
}

inline ll GetSphi(uint n){
	if(n<=S)
		return Sphi[n];
	if(MSphi[n])
		return MSphi[n];
	reg ll ans=(((ll)n*(n+1))>>1);
	for(reg uint l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=1ll*(r-l+1)*GetSphi(n/l);
	}
	return MSphi[n]=ans;
}

inline ll GetSmu(uint n){
	if(n<=S)
		return Smu[n];
	if(MSmu[n])
		return MSmu[n];
	reg int ans=1;
	for(reg uint l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=(r-l+1)*GetSmu(n/l);
	}
	return MSmu[n]=ans;
}

int main(void){
	Init();
	reg int T=read();
	while(T--){
		reg uint n=read();
		printf("%lld %lld\n",GetSphi(n),GetSmu(n));
	}
	return 0;
}
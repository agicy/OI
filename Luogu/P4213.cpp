#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXS=1e7+5;

bool vis[MAXS];
int cnt,prime[MAXS];
int phi[MAXS],mu[MAXS];
ll Sphi[MAXS],Smu[MAXS];
map<int,ll> MSmu,MSphi;
int S=1e7;

inline void Init(void){
	mu[1]=phi[1]=1;
	for(reg int i=2;i<=S;++i){
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
			else{
				mu[i*prime[i]]=-mu[i];
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			}
		}
	}
	for(reg int i=1;i<=S;++i){
		Smu[i]=Smu[i-1]+mu[i];
		Sphi[i]=Sphi[i-1]+phi[i];
	}
	return;
}

inline ll GetSummu(int n){
	if(n<=S)
		return Smu[n]; 
	if(MSmu[n])
		return MSmu[n];
	reg ll res=1;
	for(reg int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		res-=(r-l+1)*GetSummu(n/l);
	}
	return MSmu[n]=res;
}

inline ll GetSumphi(int n){
	if(n<=S)
		return Sphi[n];
	if(MSphi[n])
		return MSphi[n];
	reg ll res=(1ll*n*(n+1))/2ll;
	for(reg int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		res-=(r-l+1)*GetSumphi(n/l);
	}
	return MSphi[n]=res;
}

int main(void){
	Init();
	reg int T=read();
	while(T--){
		reg int n=read();
		printf("%lld %lld\n",GetSumphi(n),GetSummu(n));
	}
	return 0;
}

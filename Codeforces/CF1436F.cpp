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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+1;
const int p=998244353;

inline ll fpow(reg ll x,reg ll exp){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%p;
		x=x*x%p;
		exp>>=1;
	}
	return res;
}

bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	return;
}

int A[MAXN];

int main(void){
	Init(1e5);
	reg int m=read();
	while(m--){
		static int a,b;
		a=read(),b=read();
		A[a]=b;
	}
	reg ll ans=0;
	for(reg int i=1;i<MAXN;++i){
		reg ll sum=0,sumi=0,sumi2=0;
		for(reg int j=i;j<MAXN;j+=i){
			sum+=A[j];
			sumi=(sumi+1ll*A[j]*j)%p;
			sumi2=(sumi2+1ll*A[j]*j%p*j)%p;
		}
		if(sum<2)
			continue;
		reg ll t1=sumi2*fpow(2,sum-2)%p*((sum-1)%p)%p;
		reg ll n2=(sumi*sumi+p-sumi2)%p;
		reg ll t2=fpow(2,sum-2);
		if(sum>=3)
			t2=(t2+((sum-2)%p)*fpow(2,sum-3))%p;
		t2=t2*n2%p;
		ans=(ans+((t1+t2)%p*mu[i]+p))%p;
	}
	printf("%lld\n",ans);
	return 0;
}
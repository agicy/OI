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

const int MAXN=2e6+5;

bool vis[MAXN];
int prime[MAXN];
int phi[MAXN];
bool rt[MAXN];

inline void Init(reg int n){
	reg int tot=0;
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	rt[2]=rt[4]=true;
	for(reg int i=2;i<=tot;++i){
		for(reg int j=1;1ll*j*prime[i]<=n;j*=prime[i])
			rt[j*prime[i]]=true;
		for(reg int j=2;1ll*j*prime[i]<=n;j*=prime[i])
			rt[j*prime[i]]=true;
	}
	return;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int cnt,fac[MAXN];

inline void frac(reg int x){
	for(reg int i=2;i*i<=x;++i)
		if(!(x%i)){
			fac[++cnt]=i;
			while(!(x%i))
				x/=i;
		}
	if(x>1)
		fac[++cnt]=x;
	return;
}

inline bool check(reg int x,reg int n){
	if(fpow(x,phi[n],n)!=1)
		return false;
	for(reg int i=1;i<=cnt;++i)
		if(fpow(x,phi[n]/fac[i],n)==1)
			return false;
	return true;
}

inline int find(reg int n){
	for(reg int i=1;i<n;++i)
		if(check(i,n))
			return i;
	return 0;
}

int tot,ans[MAXN];

inline void get(reg int p,reg int x){
	reg int pod=1;
	for(reg int i=1;i<=phi[p];++i){
		pod=1ll*pod*x%p;
		if(gcd(i,phi[p])==1)
			ans[++tot]=pod;
	}
	return;
}

int main(void){
	Init(1e6);
	reg int T=read();
	while(T--){
		reg int n,d;
		n=read(),d=read();
		if(rt[n]){
			tot=0,cnt=0;
			frac(phi[n]);
			reg int Min=find(n);
			get(n,Min);
			sort(ans+1,ans+tot+1);
			printf("%d\n",tot);
			for(reg int i=d;i<=tot;i+=d)
				printf("%d ",ans[i]);
			puts("");
		}
		else
			puts("0\n");
	}
	return 0;
}
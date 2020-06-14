#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;

inline int Add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

inline int Mul(reg int a,reg int b){
	return 1ll*a*b%MOD;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x,reg int mod){
	return pow(x,mod-2,mod);
}

bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN];

int f[MAXN],invf[MAXN];
int F[MAXN];

inline void Init(reg int n){
	f[1]=invf[1]=F[0]=F[1]=1;
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		f[i]=(f[i-1]+f[i-2])%MOD;
		invf[i]=inv(f[i],MOD);
		F[i]=1;
		if(!vis[i]){
			mu[i]=-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=n;++i){
		if(!mu[i])
			continue;
		for(reg int j=i;j<=n;j+=i)
			F[j]=Mul(F[j],mu[i]==1?f[j/i]:invf[j/i]);
	}
	for(reg int i=2;i<=n;++i)
		F[i]=Mul(F[i],F[i-1]);
	return;
}

int n,m;

int main(void){
	Init(1e6);
	reg int T=read();
	while(T--){
		n=read(),m=read();
		if(n>m)
			swap(n,m);
		reg int ans=1;
		for(reg int l=1,r;l<=n;l=r+1){
			r=min(n/(n/l),m/(m/l));
			reg int Inv=Mul(F[r],inv(F[l-1],MOD));
			ans=Mul(ans,pow(Inv,1ll*(n/l)*(m/l)%(MOD-1),MOD));
		}
		printf("%d\n",ans);
	}
	return 0;
}
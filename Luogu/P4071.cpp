#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
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

const int MAXN=1000000+5;

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,m;

ll fac[MAXN],D[MAXN];

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

inline ll C(reg ll n,reg ll m,reg ll mod){
	return fac[n]*inv(fac[m]*fac[n-m]%mod,mod)%mod;
}

inline ll Lucas(reg ll n,reg ll m,reg ll mod){
	if(m==0)
		return 1;
	return C(n%mod,m%mod,mod)*Lucas(n/mod,m/mod,mod)%mod;
}

int main(void){
	fac[0]=1;
	for(reg int i=1;i<=1e6;++i)
		fac[i]=fac[i-1]*i%MOD;
	D[1]=0;
	D[2]=1;
	for(reg int i=3;i<=1e6;++i)
		D[i]=(D[i-1]+D[i-2])*(i-1)%MOD;
	reg int T=read();
	while(T--){
		n=read(),m=read();
		if(n==m)
			puts("1");
		else
			printf("%lld\n",(Lucas(n,m,MOD)*D[n-m])%MOD);
	}
	return 0;
}
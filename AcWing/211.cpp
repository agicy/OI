#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 10007
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

ll a,b,k,n,m;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	a=read(),b=read(),k=read(),n=read(),m=read();
	return;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%MOD;
		x=x*x%MOD;
		exp>>=1;
	}
	return res;
}

inline ll fac(reg ll x,reg ll mod){
	reg ll res=1;
	for(reg int i=2;i<=x;++i)
		res=res*i%mod;
	return res;
}

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

inline ll C(reg ll m,reg ll n,reg ll mod){
	return fac(n,mod)*inv(fac(m,MOD)*fac(n-m,MOD)%MOD,MOD)%MOD;
}

inline void Work(void){
	a%=MOD,b%=MOD;
	reg ll ans=pow(a,n,MOD)*pow(b,m,MOD)%MOD*C(min(n,m),k,MOD)%MOD;
	printf("%lld\n",ans);
	return;
}

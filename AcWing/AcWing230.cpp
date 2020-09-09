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

const int MAXN=1e6+5;
const int p=1e9+7;

int n,m;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int d[MAXN],fac[MAXN],invfac[MAXN];

inline void Init(reg int n){
	fac[0]=invfac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=1;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	d[0]=1,d[1]=0,d[2]=1;
	for(reg int i=3;i<=n;++i)
		d[i]=1ll*(d[i-1]+d[i-2])%p*(i-1)%p;
	return;
}

inline int binom(reg int n,reg int m){
	return 1ll*fac[n]*invfac[n-m]%p*invfac[m]%p;
}

int main(void){
	Init(1e6);
	reg int T=read();
	while(T--){
		n=read(),m=read();
		printf("%lld\n",1ll*binom(n,m)*d[n-m]%p);
	}
	return 0;
}
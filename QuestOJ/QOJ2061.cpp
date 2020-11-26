#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}
inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e6+5;

int n,m,p;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline void exgcd(reg int a,reg int b,reg int &x,reg int &y){
	if(!b){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	reg int tmp=x;
	x=y;
	y=tmp-a/b*y;
	return;
}

inline int inv(reg int a,reg int p){
	int x,y;
	exgcd(a,p,x,y);
	return x<0?x+p:x;
}

inline int fpow(reg ll x,reg ll exp,reg ll mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int G(reg ll n,reg int p){
	if(n<p)
		return 0;
	else
		return G(n/p,p)+(n/p);
}

inline int f(reg ll n,reg int p,reg int pk){
	if(n==0)
		return 1;
	reg int s=1,r=1;
	for(reg int i=1;i<=pk;++i)
		if(i%p)
			s=1ll*s*i%pk;
	s=fpow(s,n/pk,pk);
	for(reg ll i=pk*(n/pk);i<=n;++i)
		if(i%p)
			r=1ll*r*(i%pk)%pk;
	return 1ll*f(n/p,p,pk)*s%pk*r%pk;
}

inline int C_PK(reg ll n,reg ll m,reg int p,reg int pk){
	reg int F=f(n,p,pk),fm1=inv(f(m,p,pk),pk),fm2=inv(f(n-m,p,pk),pk);
	reg int mi=fpow(p,G(n,p)-G(m,p)-G(n-m,p),pk);
	return 1ll*F*fm1%pk*fm2%pk*mi%pk;
}

const int MAXS=1e6+5;

inline int exLucas(reg ll n,reg ll m,reg int p){
	static int a[MAXS],b[MAXS];
	reg int tmp=p,tot=0;
	if(p!=1e9+7)
		for(reg int i=2;i*i<=tmp;++i){
			if(tmp%i==0){
				reg int pod=1;
				while(tmp%i==0){
					pod*=i;
					tmp/=i;
				}
				a[++tot]=pod,b[tot]=C_PK(n,m,i,pod);
			}
		}
	if(tmp!=1)
		a[++tot]=tmp,b[tot]=C_PK(n,m,tmp,tmp);
	reg int ans=0;
	for(reg int i=1;i<=tot;++i){
		reg ll m=p/a[i],t=inv(m,a[i]);
		ans=(ans+1ll*b[i]*m%p*t%p)%p;
	}
	return ans;
}

signed main(void){
	n=readll(),m=readll(),p=read();
	if(p==1e9+7){
		reg int ans1=1,ans2=1;
		for(reg int i=1;i<=n+m;++i)
			ans1=1ll*ans1*i%p;
		for(reg int i=1;i<=m;++i)
			ans2=1ll*ans2*i%p;
		for(reg int i=1;i<=n;++i)
			ans2=1ll*ans2*i%p;
		printf("%lld\n",1ll*ans1*inv(ans2,p)%p);
	}
    else
	    printf("%lld\n",exLucas(n+m,m,p));
	return 0;
}
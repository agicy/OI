#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=10+5;

int n;
ll a[MAXN],b[MAXN];

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}

inline ll add(reg ll a,reg ll b,reg ll p){
	a+=b;
	return a>=p?a-p:a;
}

inline ll mul(reg ll a,reg ll b,reg ll p){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,p);
		a=add(a,a,p);
		b>>=1;
	}
	return res;
}

inline ll inv(reg ll x,reg ll p){
	ll tmp,inv;
	exgcd(x,p,inv,tmp);
	return (inv%p+p)%p;
}

inline ll CRT(reg int n,reg ll a[],reg ll b[]){
	reg ll M=1;
	for(reg int i=1;i<=n;++i)
		M*=a[i];
	reg ll res=0;
	for(reg int i=1;i<=n;++i){
		reg ll m=M/a[i];
		reg ll t=inv(m%a[i],a[i]);
		reg ll tmp=mul(mul(b[i],m,M),t,M);
		res=add(res,tmp,M);
	}
	return res;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	printf("%lld\n",CRT(n,a,b));
	return 0;
}
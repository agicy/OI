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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void No(void){
	puts("NO"),exit(0);
	return;
}

inline void Yes(void){
	puts("YES"),exit(0);
	return;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	if(b<0)
		a=-a,b=-b;
	reg ll res=0;
	while(b){
		if(b&1)
			res=(res+a)%mod;
		a=(a+a)%mod;
		b>>=1;
	}
	return res;
}

inline ll fpow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

inline ll lcm(reg ll a,reg ll b){
	return a/gcd(a,b)*b;
}

inline ll CRT(reg ll r[],reg ll m[],reg int n){
	reg ll lcm=m[1],res=r[1];
	for(reg int i=2;i<=n;++i){
		reg ll a=lcm,b=m[i],c=r[i]-res;
		ll x,y;
		reg ll d=exgcd(a,b,x,y);
		if(c%d)
			return -1;
		a/=d,b/=d,c/=d;
		x=(mul(x,c,b)+b)%b;
		res+=x*lcm,lcm*=m[i]/d,res=(res+lcm)%lcm;
	}
	res=(res+lcm-1)%lcm+1;
	return res;
}

const int MAXK=1e4+5;

ll n,m;
int k;
ll a[MAXK];
ll r[MAXK];

int main(void){
	n=readll(),m=readll(),k=read();
	reg ll x=1;
	for(reg int i=1;i<=k;++i){
		a[i]=readll();
		x=lcm(x,a[i]);
		if(x>n)
			No();
		r[i]=((a[i]-i+1)%a[i]+a[i])%a[i];
	}
	reg ll y=CRT(r,a,k);
	if(y==-1||y<1||y+k-1>m)
		No();
	else{
		for(reg int i=1;i<=k;++i)
			if(gcd(x,y+i-1)!=a[i])
				No();
		Yes();
	}
	return 0;
}
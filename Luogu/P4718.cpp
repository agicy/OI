#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

inline bool Miller_Rabin(reg ll x,reg ll b){
	reg ll k=x-1;
	while(k){
		reg ll cur=pow(b%x,k%x,x);
		if(cur!=1&&cur!=x-1)
			return false;
		if((k&1)==1||cur==x-1)
			return true;
		k>>=1;
	}
	return true;
}

inline bool isPrime(reg ll x){
	if(x==46856248255981ll||x<2)
		return false;
	if(x==2||x==3||x==7||x==61||x==24251)
		return true;
	return Miller_Rabin(x,2)&&Miller_Rabin(x,61);
}

inline ll f(reg ll x,reg ll c,reg ll mod){
	return add(mul(x,x,mod),c,mod);
}

inline ll Pollard_Rho(reg ll x){
	reg ll s=0,t=0,c=1ll*rand()%(x-1)+1,val=1;
	for(reg int goal=1;;goal<<=1,s=t,val=1){
		for(reg int stp=1;stp<=goal;++stp){
			t=f(t,c,x);
			val=mul(val,abs(t-s),x);
			if((stp%127)==0){
				reg ll d=gcd(val,x);
				if(d>1)
					return d;
			}
		}
		reg ll d=gcd(val,x);
		if(d>1)
			return d;
	}
}

ll Maxfac;

inline void fac(reg ll x){
	if(x<=Maxfac||x<2)
		return;
	if(isPrime(x)){
		Maxfac=Maxfac>x?Maxfac:x;
		return;
	}
	reg ll p=x;
	while(p>=x)
		p=Pollard_Rho(x);
	while((x%p)==0)
		x/=p;
	fac(x),fac(p);
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		srand((unsigned)time(NULL));
		reg ll n=read();
		Maxfac=0;
		fac(n);
		if(Maxfac==n)
			puts("Prime");
		else
			printf("%lld\n",Maxfac);
	}
	return 0;
}
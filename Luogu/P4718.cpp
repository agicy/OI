#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

#define mul(a,b,mod) ( (__int128) (a) * (b) % (mod) )

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

inline bool Miller_Rabin(reg ll n){
	const int TEST_TIMES=4;
	reg ll u=n-1,t=0;
	while((u&1)==0)
		++t,u>>=1;
	for(reg int i=1;i<=TEST_TIMES;++i){
		reg ll x=rand()%(n-2)+2,v=pow(x,u,n);
		if(v==1||v==n-1)
			continue;
		reg int j;
		for(j=0;j<t;++j){
			v=mul(v,v,n);
			if(v==n-1)
				break;
		}
		if(j>=t)
			return false;
	}
	return true;
}

inline bool isPrime(reg ll n){
	if(n<3)
		return n==2;
	else if(n==3||n==5||n==7||n==11||n==13||n==17||n==19||n==23||n==29||n==31||n==37||n==41||n==43||n==47||n==53||n==59||n==61||n==67||n==71||n==73||n==79||n==83||n==89||n==97)
		return true;
	else if(n==24251)
		return true;
	else if(n<=100||n==46856248255981ll)
		return false;
	return Miller_Rabin(n);
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll f(reg ll x,reg ll c,reg ll mod){
	return (mul(x,x,mod)+c)%mod;
}

inline ll Pollard_Rho(reg ll n){
	if(n==4)
		return 2;
	if(isPrime(n))
		return n;
	reg ll c=rand()%(n-1)+1,u=f(0,c,n),v=f(f(0,c,n),c,n);
	while(u!=v){
		reg ll d=gcd(abs(u-v),n);
		if(d>1)
			return d;
		u=f(u,c,n),v=f(f(v,c,n),c,n);
	}
	return n;
}

ll ans;

inline void frac(reg ll n){
	if(n<ans)
		return;
	if(isPrime(n)){
		ans=max(ans,(ll)n);
		return;
	}
	reg ll a=n;
	a=Pollard_Rho(n);
	while(n%a==0)
		n/=a;
	frac(a),frac(n);
	return;
}

int main(void){
	srand((ull)time(0));
	int T=read();
	while(T--){
		ll n=read();
		if(isPrime(n))
			puts("Prime");
		else{
			ans=0;
			frac(n);
			printf("%lld\n",ans);
		}
	}
	return 0;
}

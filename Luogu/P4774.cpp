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

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}

inline ll add(reg ll a,reg ll b,reg ll mod){
	a+=b;
	return a>=mod?a-mod:a;
}

inline ll sub(reg ll a,reg ll b,reg ll mod){
	a-=b;
	return a<0?a+mod:a;
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

int n,m;
ll a[MAXN],p[MAXN];
ll t[MAXN];
ll b[MAXN];
multiset<ll> S;
ll Max;

inline ll exCRT(reg int n,reg ll a[],reg ll p[]){
	reg ll ans=0,lcm=1;
	ll x,y,gcd;
	for(reg int i=1;i<=n;++i){
		reg ll A=mul(b[i],lcm,p[i]),B=p[i],C=sub(a[i],mul(b[i],ans,p[i]),p[i]);
		gcd=exgcd(A,B,x,y),x=add(x,B,B);
		if(C%gcd)
			return -1;
		reg ll tmp=mul(C/gcd,x,B/gcd);
		ans=add(ans,mul(tmp,lcm,lcm*(B/gcd)),lcm*(B/gcd));
		lcm*=B/gcd;
	}
	if(ans<Max)
		ans+=((Max-ans-1)/lcm+1)*lcm;
	return ans;
}

int main(void){
	reg int T=read();
	while(T--){
		S.clear();
		Max=0;
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			a[i]=readll();
		for(reg int i=1;i<=n;++i)
			p[i]=readll();
		for(reg int i=1;i<=n;++i)
			t[i]=readll();
		for(reg int i=1;i<=m;++i){
			static ll x;
			x=readll();
			S.insert(x);
		}
		for(reg int i=1;i<=n;++i){
			multiset<ll>::iterator it=S.upper_bound(a[i]);
			if(it!=S.begin())
				--it;
			b[i]=*it,S.erase(it),S.insert(t[i]);
			Max=max(Max,(a[i]-1)/b[i]+1);
		}
		printf("%lld\n",exCRT(n,a,p));
	}
	return 0;
}
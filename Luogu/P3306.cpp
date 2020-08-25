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

ll p,a,b,x1,t;

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	return a*b%mod;
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
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

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

const int MAXSIZE=2;

map<ll,ll> M;

inline ll bsgs(reg ll a,reg ll b,reg ll p){
	reg ll m=sqrt(p)+1;
	M.clear();
	a%=p,b%=p;
	if(!a&&b)
		return -1;
	for(ll i=0,t=b;i<m;++i,t=mul(t,a,p))
		M[t]=i;
	for(ll i=1,w=pow(a,m,p),t=w;i<=m+1;++i,t=mul(t,w,p))
		if(M.find(t)!=M.end())
			return i*m-M[t];
	return -1;
}

int main(void){
	reg int T=read();
	while(T--){
		p=read(),a=read(),b=read(),x1=read(),t=read();
		if(x1==t)
			puts("1");
		else if(a==0)
			if(b==t)
				puts("2");
			else
				puts("-1");
		else if(a==1){
			reg ll d=gcd(b,p);
			if((t-x1)%d)
				puts("-1");
			else
				printf("%lld\n",mul(add(t,p-x1,p),inv(b,p),p)+1);
		}
		else{
			reg ll ans=bsgs(a,mul(add(t,mul(b,inv(a-1,p),p),p),inv(add(x1,mul(b,inv(a-1,p),p),p),p),p),p);
			printf("%lld\n",ans==-1?-1:ans+1);
		}
	}
	return 0;
}
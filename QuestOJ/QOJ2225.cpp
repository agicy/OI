#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
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

const int MAXSIZE=10000+5;

inline bool Miller_Rabin(reg ll n,reg ll base){
	reg ll d=n-1,p=0;
	while(!(d&1))
		d>>=1,++p;
	reg ll cur=pow(base%n,d,n);
	if(cur==1||cur==n-1)
		return true;
	for(reg int i=1;i<=p;++i){
		cur=mul(cur,cur,n);
		if(cur==n-1)
			return true;
	}
	return false;
}

inline bool Miller_Rabin(reg ll n){
	if(n==46856248255981||n<2)
		return false;
	if(n==2||n==3||n==7||n==61||n==24251)
		return true;
	return Miller_Rabin(n,2)&&Miller_Rabin(n,3)&&Miller_Rabin(n,7)&&Miller_Rabin(n,61)&&Miller_Rabin(n,24251);
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll Pollard_Rho(reg ll n){
	reg ll i=0,k=2,x=rand()%(n-1)+1,y=x;
	reg int c=rand();
	while(true){
		++i;x=(mul(x,x,n)+c)%n;
		reg ll Gcd=gcd((y-x+n)%n,n);
		if(Gcd!=1&&Gcd!=n)
			return Gcd;
		if(x==y)
			return n;
		if(i==k)
			k<<=1,y=x;
	}
	return n;
}

int tot;
ll fac[MAXSIZE];

inline void Div(reg ll n){
	if(n==1)
		return;
	if(Miller_Rabin(n)){
		fac[++tot]=n;
		return;
	}
	reg ll p=n;
	while(p>=n)
		p=Pollard_Rho(n);
	Div(p),Div(n/p);
	return;
}

inline void Solve(reg ll n){
	tot=0;
	Div(n);
	sort(fac+1,fac+tot+1);
	reg int m=unique(fac+1,fac+tot+1)-(fac+1);
	reg int ans=1;
	for(reg int i=1;i<=m;++i)
		ans=1ll*ans*(fac[i]%MOD+1ll)%MOD;
	printf("%d\n",ans);
	return;
}

int main(void){
	reg int T=read();
	while(T--)
		Solve(read());
	return 0;
}
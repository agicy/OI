#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
ll a[MAXN],b[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read(),a[i]=read();
	return;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=(res+a)%mod;
		a=(a<<1)%mod;
		b>>=1;
	}
	return res;
}

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	reg ll gcd=exgcd(b,a%b,x,y);
	reg ll temp=x;
	x=y;
	y=temp-a/b*y;
	return gcd;
}

inline void Work(void){
	reg ll ans=a[1],M=b[1];
	for(reg int i=2;i<=n;++i){
		reg ll A=M,B=b[i],C=(a[i]-ans%B+B)%B;
		ll x,y;
		reg ll gcd=exgcd(A,B,x,y);
		reg ll bg=B/gcd;
		if(C%gcd!=0)
			exit(0);
		x=mul(x,C/gcd,bg);
		ans+=x*M;
		M*=bg;
		ans=(ans%M+M)%M;
	}
	ans=(ans%M+M)%M;
	printf("%lld\n",ans);
	return;
}

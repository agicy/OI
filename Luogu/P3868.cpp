#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;

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

inline void exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(b==0){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	reg ll temp=x;
	x=y;
	y=temp-a/b*y;
	return;
}

int n;
ll a[MAXN],b[MAXN];

inline ll CRT(void){
	reg ll ans=0,lcm=1;
	ll x,y;
	for(reg int i=1;i<=n;++i)
		lcm*=b[i];
	for(reg int i=1;i<=n;++i){
		reg ll temp=lcm/b[i];
		exgcd(temp,b[i],x,y);
		x=(x%b[i]+b[i])%b[i];
		ans=(ans+mul(mul(temp,x,lcm),a[i],lcm))%lcm;
	}
	return (ans+lcm)%lcm;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	for(reg int i=1;i<=n;++i)
		a[i]=(a[i]%b[i]+b[i])%b[i];
	printf("%lld\n",CRT());
	return 0;
}
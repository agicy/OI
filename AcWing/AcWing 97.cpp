#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 9901
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

const int MAXA=5000000+5;

int a,b;
int tot,p[MAXA],cnt[MAXA];

inline ll pow(reg ll,reg ll,reg ll);
inline ll inv(reg ll,reg ll);
inline void Divide(reg int);

int main(void){
	reg ll ans=1;
	a=read(),b=read();
	if(a==0)
		return puts("0"),0;
	if(b==0)
		return puts("1"),0;
	Divide(a);
	for(reg int i=1;i<=tot;++i)
		if(p[i]!=9901)
			ans=ans*(pow(p[i],(ll)cnt[i]*b+1,MOD)-1+MOD)%MOD*inv(p[i]-1,MOD)%MOD;
	printf("%lld\n",ans);
	return 0;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

inline void Divide(reg int a){
	for(reg int i=2;i<=a;++i){
		if(a%i==0){
			p[++tot]=i;
			while(a%i==0){
				++cnt[tot];
				a/=i;
			}
		}
	}
	if(a!=1){
		cnt[tot]=1;
		p[++tot]=a;
	}
	return;
}
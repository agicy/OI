#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353
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

const int MAXN=70000000+5;
const int MAXP=100+5;

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

int n;
int p[MAXN];
ll inv[MAXP];
ll dp[MAXN];

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	Init();
	Read();
	Work();
	return 0;
}

inline void Init(void){
	reg ll inv100=pow(100,MOD-2,MOD);
	for(reg int i=1;i<=100;++i)
		inv[i]=pow(inv100*i%MOD,MOD-2,MOD);
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		dp[i]=(dp[i-1]+1)*inv[p[i]]%MOD;
	printf("%lld\n",dp[n]);
	return;
}
